import re

file = open("data.txt", "r")
instructions, nodes = file.read().split("\n\n")

nodes = nodes.split("\n")

node_dict = {}

for node in nodes:
    node_dict[node[0:3]] = [node[7:10], node[12:15]]
print(node_dict)
curr_node = "AAA"
num = 0
while curr_node != "ZZZ":
    for dir in instructions:
        num += 1
        if dir == "L":
            curr_node = node_dict[curr_node][0]
        elif dir == "R":
            curr_node = node_dict[curr_node][1]
        else:
            print("Invalid direction")
        if curr_node == "ZZZ":
            print("ZZZ!")
            break

print(num)
    