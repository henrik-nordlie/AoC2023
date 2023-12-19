import numpy as np

file = open("data.txt", "r")
lines = file.read().split("\n")
file.close()

galaxies = []
empty_cols = np.ones(len(lines[0]))
empty_rows = np.ones(len(lines))
for i, line in enumerate(lines[:-1]):
    for j, char in enumerate(line):
        if char == "#":
            empty_cols[j] = 0
            empty_rows[i] = 0

x_pos = 0
for i, line in enumerate(lines[:-1]):
    if empty_rows[i] == 1:
        x_pos += 1000000
        continue
    y_pos = 0
    for j, char in enumerate(line):
        if char == "#":
            galaxies.append((x_pos, y_pos))
        if empty_cols[j] == 1:
            y_pos += 1000000
        else:
            y_pos += 1
    x_pos += 1


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
