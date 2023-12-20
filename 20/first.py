from queue import Queue

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

def traverse(G, starting_point, signal, flip_flops, conjunctions):
    q = Queue()
    q.put((starting_point, starting_point, signal))
    low_signals = 0
    high_signals = 0
    while q.empty() == False:
        previous, current, signal = q.get()
        if signal == 0:
            low_signals += 1
        else:
            high_signals += 1
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
    return (low_signals, high_signals)

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

steps_to_do = 1000
lows = 0
highs = 0
for i in range(steps_to_do):
    l, h = traverse(G, 'broadcaster', 0, flip_flops, conjunctions)
    lows += l
    highs += h

print(lows * highs)