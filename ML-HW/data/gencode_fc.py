fc_id = 0
filename = 'weights/Linear(in_features=30, out_features=9, bias=False).csv'
with open(filename) as rf:
    for kernel_id in range(0, 9):
        str = rf.readline()
        if str == '':
            break
        str = str[:str.find('\n')].split(',')
        print(f'//FC{fc_id}_node{kernel_id}')
        print(f'wire signed[15:0] fc{fc_id}_node{kernel_id}_c[29:0];')
        for idx in range(0, len(str)):
            val = str[idx]
            assign_str = f'assign fc{fc_id}_node{kernel_id}_c[{idx}] = 16\'h{val};'
            print(assign_str)
        print('\n')

fc_id = 1
filename = 'weights/Linear(in_features=9, out_features=5, bias=False).csv'
with open(filename) as rf:
    for kernel_id in range(0, 5):
        str = rf.readline()
        if str == '':
            break
        str = str[:str.find('\n')].split(',')
        print(f'//FC{fc_id}_node{kernel_id}')
        print(f'wire signed[15:0] fc{fc_id}_node{kernel_id}_c[8:0];')
        for idx in range(0, len(str)):
            val = str[idx]
            assign_str = f'assign fc{fc_id}_node{kernel_id}_c[{idx}] = 16\'h{val};'
            print(assign_str)
        print('\n')