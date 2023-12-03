import re

f = open("data.txt", "r")
#f = open("test.txt", "r")
lines = f.readlines()

def gather_symbols(lines):
    syms = []
    for line in lines:
        for char in line:
            if not char.isnumeric() and char != "." and char != "\n":
                if char not in syms:
                    syms.append(char)
    return syms

def get_neighbours(loc):
    neighbours = [[loc[0]+1, loc[1]], 
                  [loc[0]-1, loc[1]], 
                  [loc[0], loc[1]+1], 
                  [loc[0], loc[1]-1], 
                  [loc[0]+1, loc[1]+1], 
                  [loc[0]-1, loc[1]-1], 
                  [loc[0]+1, loc[1]-1], 
                  [loc[0]-1, loc[1]+1]] 
    return neighbours


number_locs = []
symbol_locs = []

gear_ratios = []

def find_num(line, loc):
    start = loc
    num = line[loc]
    while line[loc-1].isnumeric():
        num = line[loc-1]+num
        loc -= 1
    loc = start
    while line[loc+1].isnumeric():
        num += line[loc+1]
        loc += 1
    return int(num)


for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if char == "*":
            hit = False
            neighbours = get_neighbours([i,j])
            for neighbour in neighbours:
                    if neighbour[0] >= 0 and neighbour[0] < len(lines) and neighbour[1] >= 0 and neighbour[1] < len(line):
                        if lines[neighbour[0]][neighbour[1]].isnumeric():
                            if not hit:
                                num = find_num(lines[neighbour[0]], neighbour[1])
                                hit = True
                            else:
                                if num != find_num(lines[neighbour[0]], neighbour[1]):
                                    gear_ratios.append(num*find_num(lines[neighbour[0]], neighbour[1]))
                                    break

print(sum(gear_ratios))

