import sys

sys.setrecursionlimit(10000)

directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
def dfs(grid, position, target, n, m, visited = set()):
    visited.add(position)
    if position == target:
        return len(visited) - 1
    symbol = grid[position[0]][position[1]]
    directions_to_visit = []
    result = -1
    if symbol != '.':
        directions_to_visit.append(directions['^>v<'.index(symbol)])
    else:
        directions_to_visit = directions
    for di, dii in directions_to_visit:
        new_i, new_ii = position[0] + di, position[1] + dii
        if new_i >= 0 and new_ii >= 0 and new_i < n and new_ii < m and grid[new_i][new_ii] != '#':
            if (new_i, new_ii) not in visited:
                new_visited = set(visited)
                result = max(result, dfs(grid, (new_i, new_ii), target, n, m, new_visited))
    
    return result

grid = open('input2.txt').read().splitlines()
n = len(grid)
m = len(grid[0])

result = dfs(grid, (0, 1), (n - 1, m - 2), n, m)

print(result)