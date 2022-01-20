conv_id = 0
for kernel_id in range(5):
    filename = f'weights/Conv1d(1, 5, kernel_size=(5,), stride=(2,), bias=False)_{kernel_id}.csv'
    with open(filename) as rf:
        while True:
            str = rf.readline()
            if str == '':
                break
            str = str[:str.find('\n')].split(',')
            print(f'//conv{conv_id} kernel{kernel_id} coeff')
            print(f'wire signed[15:0] conv{conv_id}_kernel{kernel_id}_c[4:0];')
            for idx in range(0, len(str)):
                val = str[idx]
                assign_str = f'assign conv{conv_id}_kernel{kernel_id}_c[{idx}] = 16\'h{val};'
                print(assign_str)
            print('\n')

conv_id = 1
for kernel_id in range(2):
    filename = f'weights/Conv1d(5, 2, kernel_size=(5,), stride=(2,), bias=False)_{kernel_id}.csv'
    with open(filename) as rf:
        channel_id = 0
        while True:
            str = rf.readline()
            if str == '':
                break
            str = str[:str.find('\n')].split(',')
            print(f'//conv{conv_id} kernel{kernel_id}_{channel_id} coeff')
            print(f'wire signed[15:0] conv{conv_id}_kernel{kernel_id}_{channel_id}_c[4:0];')
            for idx in range(0, len(str)):
                val = str[idx]
                assign_str = f'assign conv{conv_id}_kernel{kernel_id}_{channel_id}_c[{idx}] = 16\'h{val};'
                print(assign_str)
            print('\n')
            channel_id += 1
