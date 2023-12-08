import re
import math
from functools import reduce

file = open("data.txt", "r")
instructions, nodes = file.read().split("\n\n")

nodes = nodes.split("\n")

node_dict = {}

for node in nodes[:-1]:
    node_dict[node[0:3]] = [node[7:10], node[12:15]]

curr_nodes = []
for node in node_dict:
    if node[2] == "A":
        curr_nodes.append(node)
print(curr_nodes)

end_nodes = []
for node in node_dict:
    if node[2] == "Z":
        end_nodes.append(node)


def find_path_length(start_node, node_dict, instructions):
    curr_node = start_node
    num = 0
    while curr_node[2] != "Z":
        for dir in instructions:
            num += 1
            if dir == "L":
                curr_node = node_dict[curr_node][0]
            elif dir == "R":
                curr_node = node_dict[curr_node][1]
            else:
                print("Invalid dir")
    return num

path_lengths = []
for node in curr_nodes:
    path_lengths.append(find_path_length(node, node_dict, instructions))

print(path_lengths)
    
lcm = reduce(lambda x, y: math.lcm(x, y), path_lengths)

print(lcm)
