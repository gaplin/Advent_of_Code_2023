from queue import Queue
from math import lcm

def fill_states(G, starting_point, flip_flops, conjunctions):
    visited = set()
    q = Queue()
    q.put(starting_point)
    visited.add(starting_point)

    while q.empty() == False:
        current = q.get()
        neighbours = G[current][1:]
        for neighbour in neighbours:
            if neighbour not in visited:
                visited.add(neighbour)
                q.put(neighbour)
            if neighbour not in G:
                G[neighbour] = ['']
            node_type = G[neighbour][0]
            if node_type == '%':
                flip_flops[neighbour] = 0
            elif node_type == '&':
                if neighbour not in conjunctions:
                    conjunctions[neighbour] = {}
                conjunctions[neighbour][current] = 0

def traverse(G, starting_point, signal, flip_flops, conjunctions, cycles, step, cycles_max_len):
    q = Queue()
    one_before = 'th'
    q.put((starting_point, starting_point, signal))
    while q.empty() == False:
        previous, current, signal = q.get()
        if current == one_before and signal == 1:
            if previous not in cycles:
                cycles[previous] = step
            if len(cycles) == cycles_max_len:
                result = lcm(*(cycles.values()))
                return result
        node_type = G[current][0]
        neighbours = G[current][1:]
        if node_type == '%':
            if signal == 1:
                continue
            flip_flops[current] = (1 - flip_flops[current])
            signal = flip_flops[current]
        elif node_type == '&':
            conjunctions[current][previous] = signal
            all_high = True
            for received_signal in conjunctions[current].values():
                if received_signal == 0:
                    all_high = False
                    break
            if all_high:
                signal = 0
            else:
                signal = 1
        elif node_type != 'b':
            continue
        for neighbour in neighbours:
            q.put((current, neighbour, signal))

    return 0

input = open('input2.txt').read().splitlines()
G = {}
flip_flops = {}
conjunctions = {}
for line in input:
    source, targets = line.split(' -> ')
    targets = targets.split(', ')
    node_type = ''
    if source[0] == '%' or source[0] == '&':
        node_type = source[0]
        source = source[1:]
    elif source == 'broadcaster':
        node_type = 'b'
    G[source] = [node_type, *targets]

fill_states(G, 'broadcaster', flip_flops, conjunctions)
one_before = 'th'
to_th = []
for node, props in G.items():
    if 'th' in props:
        to_th.append(node)

steps_to_do = 10000000
result = 0
cycles = {}
for i in range(steps_to_do):
    result = traverse(G, 'broadcaster', 0, flip_flops, conjunctions, cycles, i + 1, len(to_th))
    if result > 0:
        break

print(result)