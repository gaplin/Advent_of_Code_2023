input = open('input.txt', 'r').read().splitlines()

directions = {'R': (0, 1), 'L': (0, -1), 'U': (-1, 0), 'D': (1, 0)}
moves = []

for line in input:
    line = line.split()
    moves.append((line[0], int(line[1])))

X = [0, 0]
Y = [0, 0]
starting_position = [0, 0]
step_count = 0
for move, steps in moves:
    step_count += steps
    dy, dx = directions[move]
    starting_position[0] += steps * dy
    starting_position[1] += steps * dx
    X[0] = min(X[0], starting_position[1])
    X[1] = max(X[1], starting_position[1])
    Y[0] = min(Y[0], starting_position[0])
    Y[1] = max(Y[1], starting_position[0])

dx = starting_position[1] - X[0]
if dx > 0:
    starting_position[1] += dx
    X[0] += dx
    X[1] += dx
dy = starting_position[0] - Y[0]
if dy > 0:
    starting_position[0] += dy
    Y[0] += dy
    Y[1] += dy

n = Y[1] + 1
m = X[1] + 1

grid = [['.' for _ in range(m)] for _ in range(n)]

position = list(starting_position)
for move, steps in moves:
    dy, dx = directions[move]
    for _ in range(steps):
        grid[position[0]][position[1]] = '#'
        position[0] += dy
        position[1] += dx

result = grid[n - 1].count('#')  
for i in range(n - 1):
    walls = 0
    for ii in range(m):
        if grid[i][ii] == '#':
            result += 1
            if grid[i + 1][ii] == '#':
                walls += 1
        elif walls % 2 == 1:
            result += 1
    
print(result)