import networkx

input = open('input2.txt').read().splitlines()

G = networkx.Graph()
for line in input:
    node, neighbours = line.split(':')
    neighbours = neighbours.strip().split(' ')
    for v in neighbours:
        G.add_edge(node, v)
        G.add_edge(v, node)

G.remove_edges_from(networkx.minimum_edge_cut(G))
a, b = networkx.connected_components(G)
print(len(a) * len(b))