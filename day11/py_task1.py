import numpy as np

file = open("data.txt", "r")
lines = file.read().split("\n")
file.close()

galaxies = []
expanded_galxy = []
empty_cols = np.ones(len(lines[0]))
for i, line in enumerate(lines[:-1]):
    all_empty = True
    for j, char in enumerate(line):
        if char == "#":
            empty_cols[j] = 0
            all_empty = False
    if all_empty:
        expanded_galxy.append(line)
    expanded_galxy.append(line)

for i in range(len(empty_cols)-1, -1, -1):
    if empty_cols[i] == 1:
        for j, line in enumerate(expanded_galxy):
            expanded_galxy[j] = line[:i] + "." + line[i:]
    
for i, line in enumerate(lines[:-1]):
    print(line)


print("\n")

for line in expanded_galxy:
    print(line)


for i, line in enumerate(expanded_galxy):
    for j, char in enumerate(line):
        if char == "#":
            galaxies.append((i, j))


for i, galaxy in enumerate(galaxies):
    print("{0} {1} {2}".format(i+1, galaxy[0], galaxy[1]))

print("\n")

galaxy_pair_dists = []
for i in range(len(galaxies)-1):
    for j in range(i+1, len(galaxies)):
        galaxy_pair_dists.append((i+1, j+1, (abs(galaxies[j][0] - galaxies[i][0]) + abs(galaxies[j][1] - galaxies[i][1]))))

ans = 0
for pair in galaxy_pair_dists:
    print("{0} {1} {2}".format(pair[0], pair[1], pair[2]))
    print("\n")
    ans += pair[2]

print(ans)
