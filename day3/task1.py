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

number_hits = []

syms = gather_symbols(lines)
for i, line in enumerate(lines):
    for number in re.finditer(r'[\d]+', line):
        hit = False
        for j in range(number.start(), number.end()):
            if hit == False:
                neighbours = get_neighbours([i,j])
                for neighbour in neighbours:
                    if neighbour[0] >= 0 and neighbour[0] < len(lines) and neighbour[1] >= 0 and neighbour[1] < len(line):
                        if lines[neighbour[0]][neighbour[1]] in syms:
                            number_hits.append(int(number.group(0)))
                            hit = True
                            break

print(sum(number_hits))

