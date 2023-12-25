from queue import Queue

input = open('input2.txt').read().splitlines()

def get_shortest_path(source, G):
    q = Queue()
    q.put([source])
    visited = set()
    visited.add(source)
    paths = []
    while q.empty() == False:
        path = q.get()
        u = path[-1]
        if u != source:
            paths.append(path)
        for v in G[u]:
            if v not in visited:
                visited.add(v)
                path_copy = list(path)
                path_copy.append(v)
                q.put(path_copy)

    return paths

def dfs(v, G, visited = set()):
    visited.add(v)
    result = 1

    for u in G[v]:
        if u not in visited:
            result += dfs(u, G, visited)

    return result

G = {}
for line in input:
    node, neighbours = line.split(':')
    neighbours = neighbours.strip().split(' ')
    if node not in G:
        G[node] = []
    for v in neighbours:
        G[node].append(v)
        if v not in G:
            G[v] = []
        G[v].append(node)

occurs = {}
for u in G.keys():
    paths = get_shortest_path(u, G)
    for shortest_path in paths:
        for i in range(1, len(shortest_path)):
            if shortest_path[i] > shortest_path[i - 1]:
                edge = (shortest_path[i], shortest_path[i - 1])
            else:
                edge = (shortest_path[i - 1], shortest_path[i])
            if edge not in occurs:
                occurs[edge] = 0
            occurs[edge] += 1

edges = [(edge, occurs) for edge, occurs in occurs.items()]
edges.sort(key=lambda x: x[1], reverse=True)
for edge, _ in edges[:3]:
    G[edge[0]].remove(edge[1])
    G[edge[1]].remove(edge[0])

visited = set()
result = 1
components = 0
for v in G.keys():
    if v not in visited:
        result *= dfs(v, G, visited)
        components += 1

print(result, components)