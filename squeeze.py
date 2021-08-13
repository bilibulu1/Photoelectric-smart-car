

import argparse
import numpy as np
import torch

from models.common import *

if __name__ == '__main__':

    weights_path = 'E:/yolov5-master/weights/garbage2.pt'
    is_half = True

    # Load pytorch model
    model = torch.load(weights_path, map_location=torch.device('cpu'))

    net = model['model']

    if is_half:
        net.half() # 把FP32转为FP16

    # print(model)

    ckpt = {'epoch': -1,
            'best_fitness': model['best_fitness'],
            'training_results': None,
            'model': net,
            'optimizer': None}

    # Save .pt
    torch.save(ckpt, 'weights/test.pt')
    # for name, parameters in model.named_parameters():
    #     # print(name,':',parameters.size())
    #     print(parameters.dtype)
