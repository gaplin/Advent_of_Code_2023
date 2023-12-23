from queue import Queue

directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
grid = open('input2.txt').read().splitlines()
n = len(grid)
m = len(grid[0])
starting_position = (0, 1)
ending_position = (n - 1, m - 2)
cross_roads = [starting_position, ending_position]

for i in range(n):
    for ii in range(m):
        if grid[i][ii] == '#':
            continue
        neighbours_count = 0
        for di, dii in directions:
            new_i, new_ii = i + di, ii + dii
            if new_i >= 0 and new_i < n and new_ii >= 0 and new_ii < m and grid[new_i][new_ii] != '#':
                neighbours_count += 1
        if neighbours_count >= 3:
            cross_roads.append((i, ii))

G = {v: {} for v in cross_roads}

for i, ii in cross_roads:
    q = Queue()
    visited = set()
    q.put((i, ii, 0))
    visited.add((i, ii))

    while q.empty() == False:
        v_i, v_ii, dist = q.get()
        if dist > 0 and (v_i, v_ii) in cross_roads:
            G[(i, ii)][(v_i, v_ii)] = dist
            continue

        for di, dii in directions:
            new_i, new_ii = v_i + di, v_ii + dii
            if new_i >= 0 and new_i < n and new_ii >= 0 and new_ii < m and grid[new_i][new_ii] != '#' and (new_i, new_ii) not in visited:
                q.put((new_i, new_ii, dist + 1))  
                visited.add((new_i, new_ii))

def dfs(G, v, target, distance = 0, visited = set()):
    visited.add(v)
    if v == target:
        return distance
    result = -1
    for u, dist in G[v].items():
        if u not in visited:
            result = max(result, dfs(G, u, target, distance + dist, set(visited)))
    
    return result

result = dfs(G, starting_position, ending_position)
print(result)