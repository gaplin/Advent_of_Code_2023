import re

input = open("input/input.txt", "r").read().splitlines()

directions = input[0].strip()

G = {}
for line in input[2:]:
    nodes = re.findall("[A-Z]{3}", line)
    G[nodes[0]] = nodes[1:]

current_node = 'AAA'
target = 'ZZZ'

dir_idx = 0
steps = 0
while current_node != target:
    next_dir = ''
    if dir_idx == len(directions):
        dir_idx = 0
    next_dir = directions[dir_idx]
    if next_dir == 'R':
        current_node = G[current_node][1]
    else:
        current_node = G[current_node][0]
    steps += 1
    dir_idx += 1

print(steps)