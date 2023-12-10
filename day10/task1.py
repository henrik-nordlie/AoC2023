file = open("data.txt", "r")

lines = file.read().split("\n")

for i, line in enumerate(lines[:-1]):
    for j, char in enumerate(line):
        if char == "S":
            start = (i, j)

dir_dict = {"D": (-1, 0), "U": (1, 0), "R": (0, -1), "L": (0, 1)}
char_dict = {"L":["U", "R"], "J":["U", "L"], "7":["D", "L"], "F":["D", "R"], "|":["U", "D"], "-":["L", "R"]}
to_to_from = {"D": "U", "U": "D", "R": "L", "L": "R"}

def find_connections(pos, dirs):
    connections = []
    for dir in dirs:
        next_pos = (pos[0]+dir_dict[dir][0], pos[1]+dir_dict[dir][1])
        if next_pos[0] < len(lines) and next_pos[1] < len(lines[0]) and next_pos[0] >= 0 and next_pos[1] >= 0:
            char = lines[next_pos[0]][next_pos[1]]
            if char in char_dict:
                if dir in char_dict[char]:
                    go_dir = next_dir(char, dir)
                    connections.append((next_pos, go_dir))
        else:
            print("Error: Out of bounds")
    return connections # returns where key from dir_dict based on where we came from (for next step)


def next_dir(char, direction):
    if direction == char_dict[char][0]:
        return to_to_from[char_dict[char][1]] # char_dict[char][1] is where we are going, to_to_from[char_dict[char][1]] is where we came from
    else:
        return to_to_from[char_dict[char][0]]

# Find connections from start
used_pos = []
connections = find_connections(start, dir_dict)
used_pos.append(start)
for connection in connections:
    used_pos.append(connection[0])

def find_path(connections, used_pos):
    end = False
    count = 1
    while not end:
        next_connections = []
        for connection in connections:
            if not end:
               for next_connection in find_connections(connection[0], connection[1]): 
                   if next_connection[0] not in used_pos:
                       if not next_connection[0] in next_connections:
                           next_connections.append(next_connection)
                       else: # if next_connection is already in next_connections, we are at the end
                           end = True
                           break
            else:
                break
        if next_connections == []:
            end = True
            break
        count += 1
        connections = next_connections
        for next_connection in next_connections:
            used_pos.append(next_connection[0])


    used_pos.append(next_connection[0])
    return count, used_pos

count, used_pos = find_path(connections, used_pos)
print(count)
print(used_pos)


