import re
import math

input = open("input/input.txt", "r").read().splitlines()

directions = input[0].strip()

G = {}
for line in input[2:]:
    nodes = re.findall("[0-9A-Z]{3}", line)
    G[nodes[0]] = nodes[1:]


current_nodes = []
for node in G.keys():
    if str(node).endswith('A'):
        current_nodes.append(node)

cycles_lengths = []
for node in current_nodes:
    traversed_nodes = {}
    dir_idx = 0
    dir_length = len(directions)
    current_node = node
    steps = 0
    while True:
        if (current_node, steps % dir_length) not in traversed_nodes:
            traversed_nodes[(current_node, steps % dir_length)] = steps
        else:
            steps_for_first_reach = traversed_nodes[(current_node, steps % dir_length)]
            cycles_lengths.append(steps - steps_for_first_reach)
            break

        current_node = G[current_node][1 if directions[dir_idx] == 'R' else 0]
        dir_idx = (dir_idx + 1) % dir_length
        steps += 1

print(math.lcm(*cycles_lengths))