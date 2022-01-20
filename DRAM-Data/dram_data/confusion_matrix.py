

golden = []
with open('golden/golden_8497.hex', 'r') as rf:
    while True:
        l = rf.readline()
        if l == '':
            break
        golden.append(int(l[0:4]))

ground_truth = []
with open('ground_truth/ground_truth_8497.hex', 'r') as rf:
    while True:
        l = rf.readline()
        if l == '':
            break
        ground_truth.append(int(l[0:4]))

true_positive  = 0
true_negative  = 0
false_positive = 0
false_negative = 0

for i in range(0, len(golden)):
    positive = golden[i] != 0
    true     = not((ground_truth[i] == 0) ^ (golden[i] == 0))

    if true and positive:
        true_positive += 1
    elif true and not positive:
        true_negative += 1
    elif not true and positive:
        false_positive += 1
    else:
        false_negative += 1

print(f"true_positive  {true_positive}")
print(f"true_negative  {true_negative}")
print(f"false_positive {false_positive}")
print(f"false_negative {false_negative}")

mat = [[] for i in range(0, 5)]
for i in range(0, 5):
    mat[i] = [0 for i in range(0, 5)]

for i in range(0, len(golden)):
    x = ground_truth[i]
    y = golden[i]
    mat[x][y] += 1

print(mat)