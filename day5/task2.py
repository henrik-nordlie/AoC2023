import re
from copy import deepcopy

file = open("data.txt", "r")
lines = file.read().split("\n\n")
seeds = lines.pop(0).split()[1:]

map_dict = {}
for i, line in enumerate(lines):
    line = line.split("\n")
    for el in line[1:]:
        if el != "":
            vals = el.split()
            if not map_dict.get(str(i), False):
                map_dict[str(i)] = [[eval(val) for val in vals]]
            else:
                map_dict[str(i)].append([eval(val) for val in vals])

def find_union_edges(inp, filter):
    inp_start, inp_end = inp[0], inp[0]+inp[1]-1
    filter_start, filter_end = filter[0], filter[0]+filter[1]-1
    if inp_end < filter_start or inp_start > filter_end:
        return False
    else:
        return sorted([inp_start, inp_end, filter_start, filter_end])[1:3]

def merge_splits(splits):
    for i in range(len(splits)):
        if splits[i][0]+splits[i][1] == splits[i+1][0]+splits[i+1][i]:
            splits.append(splits[i][0], splits[i][1]+splits[i+1][1])
            del splits[i:i+2]

def make_splits(union_edges, chunk):
    sections = []
    if union_edges[0]-chunk[0] > 0: # first leftover split has length
        sections.append([chunk[0],union_edges[0]-chunk[0]])
    if chunk[0]+chunk[1]-1-union_edges[1] > 0:
        sections.append([union_edges[1]+1,chunk[0]+chunk[1]-1-union_edges[1]+1])
    return sections
        
chunks = []
min_vals = []
for k in range(int(len(seeds)/2)):
    print("seed num:" + str(k))
    first_seed, num = int(seeds[2*k]), int(seeds[2*k+1])
    seed_range = [first_seed, num]
    splits = [seed_range]
    for map in map_dict:
        for filter in map_dict[map]:
            filter_range = [filter[1], filter[2]]
            offset = filter[0]-filter[1]
            num_splits = len(splits)
            while num_splits > 0:
                chunk = splits[0]
                splits.pop(0)

                if not isinstance(chunk[0], int):
                    chunk = chunk[0]

                num_splits -= 1
                union_edges = find_union_edges(chunk, filter_range)
                if union_edges:
                    chunks.append([union_edges[0]+offset, union_edges[1]-union_edges[0]+1])
                    new_splits = make_splits(union_edges, chunk)
                    if new_splits != []:
                        for new_split in new_splits:
                            splits.append(new_split)
                else:
                    splits.append(chunk)

        for split in splits:
            chunks.append(split)
        splits = chunks
        chunks = []


    for split in splits:
        print(split)
        min_vals.append(split[0])
print(min(min_vals))

            


