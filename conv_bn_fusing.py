from collections import OrderedDict
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.nn.init as init

#from region_loss import RegionLoss

def save_net(fname, net):
    with h5py.File(fname, 'w') as h5f:
        for k, v in net.state_dict().items():
            h5f.create_dataset(k, data=v.cpu().numpy())
def load_net(fname, net):
    with h5py.File(fname, 'r') as h5f:
        for k, v in net.state_dict().items():        
            if k.endswith('num_batches_tracked'):
                param = torch.from_numpy(np.asarray(3560))         
            else:
                param = torch.from_numpy(np.asarray(h5f[k]))         
            v.copy_(param)

def fuse_g(conv, bn):
    
        fused = torch.nn.Conv2d(
            conv.in_channels,
            conv.out_channels,
            kernel_size=conv.kernel_size,
            stride=conv.stride,
            padding=conv.padding,
			groups=conv.in_channels,
            bias=True
        )
    
        # setting weights
        w_conv = conv.weight.clone().view(conv.out_channels, -1)
        w_bn = torch.diag(bn.weight.div(torch.sqrt(bn.eps+bn.running_var)))
        fused.weight.copy_( torch.mm(w_bn, w_conv).view(fused.weight.size()) )
        
        # setting bias
        if conv.bias is not None:
            b_conv = conv.bias
        else:
            b_conv = torch.zeros( conv.weight.size(0) )
        b_conv = torch.mm(w_bn, b_conv.view(-1, 1)).view(-1)
        b_bn = bn.bias - bn.weight.mul(bn.running_mean).div(
                              torch.sqrt(bn.running_var + bn.eps)
                            )
        fused.bias.copy_( b_conv + b_bn )
    
        return fused

def fuse(conv, bn):
    
        fused = torch.nn.Conv2d(
            conv.in_channels,
            conv.out_channels,
            kernel_size=conv.kernel_size,
            stride=conv.stride,
            padding=conv.padding,
            bias=True
        )
    
        # setting weights
        w_conv = conv.weight.clone().view(conv.out_channels, -1)
        w_bn = torch.diag(bn.weight.div(torch.sqrt(bn.eps+bn.running_var)))
        fused.weight.copy_( torch.mm(w_bn, w_conv).view(fused.weight.size()) )
        
        # setting bias
        if conv.bias is not None:
            b_conv = conv.bias
        else:
            b_conv = torch.zeros( conv.weight.size(0) )
        b_conv = torch.mm(w_bn, b_conv.view(-1, 1)).view(-1)
        b_bn = bn.bias - bn.weight.mul(bn.running_mean).div(
                              torch.sqrt(bn.running_var + bn.eps)
                            )
        fused.bias.copy_( b_conv + b_bn )
    
        return fused
		
class ReorgLayer(nn.Module):
    def __init__(self, stride=2):
        super(ReorgLayer, self).__init__()
        self.stride = stride
    def forward(self, x):
        stride = self.stride
        assert(x.data.dim() == 4)
        B = x.data.size(0)
        C = x.data.size(1)
        H = x.data.size(2)
        W = x.data.size(3)
        assert(H % stride == 0)
        assert(W % stride == 0)
        ws = stride
        hs = stride
        x = x.view([B, C, H//hs, hs, W//ws, ws]).transpose(3, 4).contiguous()
        x = x.view([B, C, H//hs*W//ws, hs*ws]).transpose(2, 3).contiguous()
        x = x.view([B, C, hs*ws, H//hs, W//ws]).transpose(1, 2).contiguous()
        x = x.view([B, hs*ws*C, H//hs, W//ws])
        return x


class SkyNet(nn.Module):
    def __init__(self):
        super(SkyNet, self).__init__()
        self.width = int(320)
        self.height = int(160)
        self.header = torch.IntTensor([0,0,0,0])
        self.seen = 0
        self.reorg = ReorgLayer(stride=2)
        
        def conv_bn(inp, oup, stride):
            return nn.Sequential(
                nn.Conv2d(inp, oup, 3, stride, 1, bias=False),
                nn.BatchNorm2d(oup),
                nn.ReLU(inplace=True)
            )
        def conv_dw(inp, oup, stride):
            return nn.Sequential(
                nn.Conv2d(inp, inp, 3, stride, 1, groups=inp, bias=False),
                nn.BatchNorm2d(inp),
                nn.ReLU6(inplace=True),
                
                nn.Conv2d(inp, oup, 1, 1, 0, bias=False),
                nn.BatchNorm2d(oup),
                nn.ReLU6(inplace=True),
            )
        self.model_p1 = nn.Sequential(
            conv_dw( 3,  48, 1),    #dw1
            nn.MaxPool2d(kernel_size=2, stride=2),
            conv_dw( 48,  96, 1),   #dw2
            nn.MaxPool2d(kernel_size=2, stride=2),
        )    
        self.model_p2 = nn.Sequential(    
            conv_dw( 96, 192, 1),   #dw3
            nn.MaxPool2d(kernel_size=2, stride=2),
            conv_dw(192, 384, 1),   #dw4
        )
        self.model_p3 = nn.Sequential(  #cat dw3(ch:192 -> 768) and dw5(ch:512)
            conv_dw(768, 96, 1),
            nn.Conv2d(96, 10, 1, 1,bias=False),
        )
        #self.loss = RegionLoss([1.4940052559648322, 2.3598481287086823,4.0113013115312155,5.760873975661669],2)
        #self.loss = RegionLoss([1.52875,2.16,4.03625,5.26625],2)
        #self.loss = RegionLoss([1.205,1.7275,2.463752,3.53,5.515,6.5475],3) 
        #self.loss = RegionLoss([1.1075,1.59875,2.29875,3.16125,3.74625,6.27875,8.88875,6.5475] ,4)
        #self.loss = RegionLoss([1.10625,1.56375,1.94,3.1975,3.3375,7.21625,3.875,3.205,8.65875,6.24],5)  
        
        #self.anchors = self.loss.anchors
        #self.num_anchors = self.loss.num_anchors
        #self.anchor_step = self.loss.anchor_step
    def forward(self, x):
        x_p1 = self.model_p1(x)
        x_p1_reorg = self.reorg(x_p1)
        x_p2 = self.model_p2(x_p1)
        x_p3_in = torch.cat([x_p1_reorg, x_p2], 1)
        x = self.model_p3(x_p3_in)
        #print(x.shape)
        return x   
torch.set_grad_enabled(False)
model = SkyNet()
weightfile    = './testmybestSkyNet().weights'		
load_net(weightfile,model)  
#x = torch.randn(1, 3, 256, 256)
model.eval()
#f1 = model.forward(x)

model2 = nn.Sequential(
    fuse_g(model.model_p1[0][0],model.model_p1[0][1]),
	model.model_p1[0][2],
    fuse(model.model_p1[0][3],model.model_p1[0][4]),
    model.model_p1[0][5],
	model.model_p1[1],
	fuse_g(model.model_p1[2][0],model.model_p1[2][1]),
	model.model_p1[2][2],
    fuse(model.model_p1[2][3],model.model_p1[2][4]),
    model.model_p1[2][5],
	model.model_p1[3],
    fuse_g(model.model_p2[0][0],model.model_p2[0][1]),
	model.model_p2[0][2],
    fuse(model.model_p2[0][3],model.model_p2[0][4]),
    model.model_p2[0][5],
	model.model_p2[1],
	fuse_g(model.model_p2[2][0],model.model_p2[2][1]),
	model.model_p2[2][2],
    fuse(model.model_p2[2][3],model.model_p2[2][4]),
	model.model_p2[2][5],	
	fuse_g(model.model_p3[0][0],model.model_p3[0][1]),
	model.model_p3[0][2],
    fuse(model.model_p3[0][3],model.model_p3[0][4]),
	model.model_p3[0][5],
	model.model_p3[1]
)

modeltype = 'myfusing'
backupdir = 'backup'
save_net('%s/%s.weights' % (backupdir,modeltype),model2)

param_list=[]
for key, value in model2.state_dict().items():
    flat_weight = value.contiguous().view(value.numel())
    param_list.extend(flat_weight.tolist())
for i in param_list:
    i = float(i)
print('param_list',len(param_list))

import struct
fp = open("myfuing.bin",'wb')
s = struct.pack('f'*len(param_list), *param_list)
fp.write(s)
	
