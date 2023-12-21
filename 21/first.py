from queue import Queue

grid = open('input2.txt').read().splitlines()
n = len(grid)
m = len(grid[0])

starting_position = (0, 0)
for i in range(n):
    for ii in range(m):
        if grid[i][ii] == 'S':
            starting_position = (i, ii)
            break

directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
limit = 64
visited = set()
q = Queue()
q.put((0, starting_position[0], starting_position[1]))
visited.add(starting_position)
result = 0

while q.empty() == False:
    distance, i, ii = q.get()
    if distance % 2 == 0:
        result += 1
    if distance == limit:
        continue

    for di, dii in directions:
        new_i, new_ii = i + di, ii + dii
        if new_i < 0 or new_i >= n or new_ii < 0 or new_ii >= m \
        or (new_i, new_ii) in visited or grid[new_i][new_ii] == '#':
            continue
        visited.add((new_i, new_ii))
        q.put((distance + 1, new_i, new_ii))

print(result)