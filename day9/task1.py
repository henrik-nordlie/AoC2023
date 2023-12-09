import re

file = open("data.txt", "r")

lines = file.read().split("\n")

def find_next(seq):
    all_diff_lists = []
    diff_list = find_diff_list(seq) 
    while not all(v == 0 for v in diff_list):
        all_diff_lists.append(diff_list)
        diff_list = find_diff_list(diff_list)
    len_all = len(all_diff_lists)
    next_num = 0
    for j in range(len_all, 0, -1):
        next_num += all_diff_lists[len_all-j][-1]
    next_num = int(seq[-1])+next_num
    return next_num
        

    
def find_diff_list(line):
    diff_list = []
    for i in range(len(line)-1):
        diff_list.append(int(line[i+1])- int(line[i]))
    return diff_list

ans = 0
for line in lines[:-1]:
    line = line.split()
    ans += find_next(line)


print(ans)
    

