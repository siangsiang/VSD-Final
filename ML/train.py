

import torch, torchvision
from torch.optim import optimizer
import torch.nn as nn
import torchvision.models as models
import torch.optim as optim 

import cv2
from PIL import Image
from torch.utils.data.dataset import Dataset 
from torch.utils.data import DataLoader
from torchvision.io import read_image
from torchvision.transforms import transforms


import numpy as np
import os
import time
from tqdm import tqdm





class myDataset(Dataset):
    def __init__(self, img_path, transform):
        self.img_path = img_path
        self.transform = transform
        self.filelist = os.listdir(os.path.join(img_path))

    def __len__(self):
        return len(self.filelist) 

    def __getitem__(self, idx):
        one_img_path = os.path.join(self.img_path, self.filelist[idx])
        
        # image = read_image(one_img_path)
        # print(type(image), image.shape)
        image = Image.open(one_img_path)

        # image.show()
        # cv2.waitKey(0)
        #print(type(image), image)

        # image = cv2.imread(one_img_path)
        # print(type(image), image.shape)

        #print(image)
        label = int(self.filelist[idx].split('_')[0])
        #print(image.getpixel((25,25)))
        if self.transform:
            image = self.transform(image)


        return image, torch.tensor(label)


def train(model, train_loader, val_loader, num_epoch):

    start_train = time.time()


    # training setting 
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    model = model.to(device)
    optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.9,weight_decay=1e-6, nesterov=True)
    scheduler = optim.lr_scheduler.MultiStepLR(optimizer,milestones=[20,40,60], gamma=0.1)
    criterion = nn.CrossEntropyLoss()


    overall_loss = np.zeros(num_epoch ,dtype=np.float32)
    overall_acc = np.zeros(num_epoch ,dtype = np.float32)

    overall_val_loss = np.zeros(num_epoch ,dtype=np.float32)
    overall_val_acc = np.zeros(num_epoch ,dtype = np.float32)

    best_acc = 0.
    for i in range(num_epoch):
        print(f'epoch = {i}')
        # epcoch setting
        start_time = time.time()
        cost = np.zeros(2, dtype=np.float32)
        train_loss = 0.0 
        corr_num = 0

        # start training
        model.train()
        for batch_idx, (data, label) in enumerate(tqdm(train_loader)):

            data = data.to(device)
            label = label.to(device)
            output = model(data) # 32 * 50
            #print(output, output.shape)

            loss_entropy = criterion(output, label)
            pre_label = output.argmax(dim=1, keepdim=True)
            # 32 * 1
            # 32

            batch_corr = pre_label.eq(label.view_as(pre_label)).sum().item()
            #print(batch_corr)
            corr_num += batch_corr
            
            optimizer.zero_grad()
            loss_entropy.backward()
            optimizer.step()

            train_loss += loss_entropy.item()
        
        scheduler.step()
        train_loss = train_loss / len(train_loader.dataset)
        train_acc = corr_num / len(train_loader.dataset)
        
        overall_loss[i], overall_acc[i] = train_loss, train_acc
    

        # start eval
        model.eval()
        with torch.no_grad():
            val_loss = 0
            val_corr = 0
            for batch_idx, (data, label) in enumerate(tqdm(val_loader)):
                data = data.to(device)
                label = label.to(device)
                output = model(data)
                pre_label = output.argmax(dim=1, keepdim=True)
                loss = criterion(output, label)
                
                val_loss += loss.item()
                batch_corr = pre_label.eq(label.view_as(pre_label)).sum().item()
                #print(batch_corr)
                val_corr += batch_corr
            val_loss = val_loss / len(val_loader.dataset)
            val_acc = val_corr / len(val_loader.dataset)
        
        overall_val_loss[i], overall_val_acc[i] = val_loss, val_acc

        #display
        end_time = time.time()
        elp_time = end_time - start_time
        min = elp_time // 60 
        sec = elp_time % 60
        print('*'*10)
        print(f'epoch = {i}')
        print('time = {:.4f} MIN {:.4f} SEC, total time = {:.4f} Min {:.4f} SEC '.format(elp_time // 60, elp_time % 60, (end_time-start_train) // 60, (end_time-start_train) % 60))
        print(f'training loss : {train_loss} ', f' train acc = {train_acc}' )
        print(f'val loss : {val_loss} ', f' val acc = {val_acc}' )
        print('========================\n')

        with open('./acc.log', 'a') as f :
            f.write(f'epoch = {i}\n', )
            f.write('time = {:.4f} MIN {:.4f} SEC, total time = {:.4f} Min {:.4f} SEC\n'.format(elp_time // 60, elp_time % 60, (end_time-start_train) // 60, (end_time-start_train) % 60))
            f.write(f'training loss : {train_loss}  train acc = {train_acc}\n' )
            f.write(f'val loss : {val_loss}  val acc = {val_acc}\n' )
            f.write('============================\n')

        # save model 
        torch.save(model.state_dict(), os.path.join('save_dir', f'epoch_{i}.pt'))
        if val_acc > best_acc:
            torch.save(model.state_dict(), os.path.join('save_dir', 'ep_{}_best_model_{:4f}.pt'.format(i,val_acc)))
            best_acc = val_acc
    
    info = np.stack((overall_acc, overall_loss, overall_val_acc, overall_val_loss), axis=0)
    np.save(os.path.join('save_dir','cost.npy'), info )


def main():

    batch_size = 32
    num_out = 50
    num_epoch = 100

    means = [0.485, 0.456, 0.406]
    stds = [0.229, 0.224, 0.225]
    train_transform = transforms.Compose([
            transforms.Resize(256),
            transforms.RandomCrop(224),
            transforms.RandomHorizontalFlip(),
            transforms.ToTensor(),
            transforms.Normalize(means, stds),
        ])

    val_transform = transforms.Compose([
            transforms.Resize(256),
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize(means, stds),
        ])
    train_set = myDataset('../data/p1_data/train_50', transform=train_transform)
    #print(train_set.datasets)
    val_set = myDataset('../data/p1_data/val_50', transform=val_transform)

    train_loader = DataLoader(train_set, batch_size=batch_size, shuffle=True, num_workers=4, pin_memory=True)
    val_loader = DataLoader(val_set, batch_size=batch_size, shuffle=False, num_workers=4, pin_memory=True)
    
    model = models.resnet50(pretrained=True)
    print(model.parameters)
    model.fc = nn.Linear(in_features=2048, out_features=num_out)
    
    train(model=model, train_loader=train_loader, val_loader=val_loader, num_epoch=num_epoch)

    
    pass


if __name__ == '__main__':
    main()


    