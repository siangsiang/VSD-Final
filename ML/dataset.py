import os
import shutil

datadir  = '../DSP/result/input_double/'
filelist = os.listdir(datadir)
# print(filelist)
cls_set = set()
for filename in filelist:
    cls_set.add(int(filename.split('_')[0])-1)
cls_set = sorted(cls_set)

cls_list = []
for cls in cls_set:
    cls_list.append([])

for filename in filelist:
    cls = int(filename.split('_')[0]) - 1
    cls_list[cls].append(filename)

for cls_filelist in cls_list:
    print(len(cls_filelist))

train_dir = os.makedirs('dataset/trainset/', exist_ok = True)
val_dir   = os.makedirs('dataset/valset/', exist_ok = True)
test_dir  = os.makedirs('dataset/testset/', exist_ok = True)

trainset_percent = 0.7
valset_percent   = 0.15
testset_percent  = 0.15

for cls_filelist in cls_list:
    n = len(cls_filelist)
    trainset_endidx = int(trainset_percent * n)
    valset_endidx   = trainset_endidx + int(valset_percent * n)
    testset_endidx  = valset_endidx + int(testset_percent * n)
    
    for i in range(0, trainset_endidx):
        src_filepath = datadir + cls_filelist[i]
        dst_filepath = 'dataset/trainset/' + cls_filelist[i]
        shutil.copy(src_filepath, dst_filepath)

    for i in range(trainset_endidx, valset_endidx):
        src_filepath = datadir + cls_filelist[i]
        dst_filepath = 'dataset/valset/' + cls_filelist[i]
        shutil.copy(src_filepath, dst_filepath)

    for i in range(valset_endidx, testset_endidx):
        src_filepath = datadir + cls_filelist[i]
        dst_filepath = 'dataset/testset/' + cls_filelist[i]
        shutil.copy(src_filepath, dst_filepath)