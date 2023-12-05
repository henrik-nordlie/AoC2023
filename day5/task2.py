import re

file = open("test.txt", "r")
lines = file.read().split("\n\n")
seeds = lines.pop(0).split()[1:]

def check_range(inp, ran_map):
    if inp < ran_map[1]+ran_map[2] and inp-ran_map[1] >= 0:
        response = ran_map[0] + (inp-ran_map[1])
        return response
    else:
        return False

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
print(map_dict)

# for seed range in seed ranges
# finn union av seed range og input ranges
# finn respo for union

def reduce_seed_range(seed_range, inp_range):
    union_range = (set(seed_range) & set(inp_range))             # range(range_map[1], range_map[1]+range_map[2]))
    return union_range


def go_down_one_map(map_dict, layer, seed_range):
    layer_ranges = map_dict[str(layer)]
    layer += 1
    respo = [seed for seed in seed_range]
    for ran in layer_ranges:
        red_ran = reduce_seed_range(seed_range, range(ran[1], ran[1]+ran[2]))
        for i, seed in enumerate(seed_range):
            if seed in red_ran:
                respo[i] = ran[0]+seed-ran[1]
    if not map_dict.get(str(layer), False): # no more layers
        print("RETURNING: \n")
        print(respo)
        return respo
    else:
        go_down_one_map(map_dict, layer, respo)

    
location_numbers = []
for k in range(int(len(seeds)/2)):
    print("seed num:" + str(k))
    first_seed, num = int(seeds[2*k]), int(seeds[2*k+1])
    seed_range = range(first_seed, first_seed+num)  
    ans = go_down_one_map(map_dict, 0, seed_range)
    location_numbers.append(ans)

print(min(location_numbers))
