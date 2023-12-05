import re

file = open("data.txt", "r")
lines = file.read().split("\n\n")
seeds = lines.pop(0)

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


location_numbers = []

for k, seed in enumerate(seeds.split()[1:]):
    response = int(seed)
    for map in map_dict:
        for ran_map in map_dict[map]:
            output = check_range(response, ran_map)
            if output:
                response = output
                break
        if not output:
            response = response
    location_numbers.append(response)

print(min(location_numbers))
