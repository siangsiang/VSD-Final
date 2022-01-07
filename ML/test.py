import random
import torch, torchvision
from torch.optim import optimizer
import torch.nn as nn
import torchvision.models as models
import torch.optim as optim 

from torch.utils.data.dataset import Dataset 
from torch.utils.data import DataLoader

import torch.nn.functional as F

import numpy as np
import os
import time
from tqdm import tqdm

import pandas as pd

class ECGDataset(Dataset):
    def __init__(self, datadir):
        self.datadir = datadir
        self.filelist = os.listdir(os.path.join(datadir))

    def __len__(self):
        return len(self.filelist) 

    def __getitem__(self, idx):
        datapath = os.path.join(self.datadir, self.filelist[idx])
        data = pd.read_csv(datapath, header=None)
        label = int(self.filelist[idx].split('_')[0])
        return torch.tensor(data.values[0], dtype=torch.float).unsqueeze(0), torch.tensor(label)

class ECGModel(nn.Module):
    def __init__(self):
        super(ECGModel, self).__init__()
        self.conv1d_1 = nn.Conv1d(in_channels=1, out_channels=5, kernel_size=5, stride=2, bias=False)
        self.relu_1   = nn.ReLU()
        self.maxp1d_1 = nn.MaxPool1d(kernel_size=2, stride=2)
        self.conv1d_2 = nn.Conv1d(in_channels=5, out_channels=2, kernel_size=5, stride=2, bias=False)
        self.relu_2   = nn.ReLU()
        self.maxp1d_2 = nn.MaxPool1d(kernel_size=2, stride=2)
        self.flatten  = nn.Flatten(start_dim=1, end_dim=-1)
        self.fc1      = nn.Linear(30, 9, bias=False)
        self.fc2      = nn.Linear(9, 5, bias=False)

    def forward(self, x):
        debug_size  = False
        shape_seq   = []
        forward_seq = [self.conv1d_1, self.relu_1, self.maxp1d_1, self.conv1d_2, self.relu_2, self.maxp1d_2, self.flatten, self.fc1, self.fc2]

        shape_seq.append(x.shape)
        for l in forward_seq:
            if hasattr(l, 'weight'):
                print(l)
                if x.ndim == 3:
                    print(x[0][0].tolist())
                if x.ndim == 2:
                    print(x[0].tolist())
            x = l(x)
            if hasattr(l, 'weight'):
                if x.ndim == 3:
                    print(l.weight[0][0].tolist())
                    print(x[0][0].tolist())
                if x.ndim == 2:
                    print(l.weight[0].tolist())
                    print(x[0].tolist())
                print("")
            if debug_size:
                shape_seq.append(x.shape)

        if debug_size:
            print(f'input size: {shape_seq[0]}')
            for i in range(1, len(shape_seq)):
                print(f'after {str(forward_seq[i-1])[:str(forward_seq[i-1]).index("(")]}: {shape_seq[i]}')
            exit(0)

        return x


def main():

    # fix ranodm seeds for reproducibility
    torch.manual_seed(0)
    random.seed(0)
    np.random.seed(0)

    model = ECGModel()
    print(model.parameters)

    model.load_state_dict(torch.load('save_dir/epoch_19.pt'))
    model.eval()

    train_set = ECGDataset('dataset/trainset')
    train_loader = DataLoader(train_set, batch_size=1, shuffle=False, num_workers=1, pin_memory=True)
    data, label = next(iter(train_loader))
    # print(data)

    model(data)
    

    pass


if __name__ == '__main__':
    main()
