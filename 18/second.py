#https://en.wikipedia.org/wiki/Pick%27s_theorem
#https://en.wikipedia.org/wiki/Shoelace_formula

input = open('input2.txt', 'r').read().splitlines()

directions = {0: (0, 1), 2: (0, -1), 3: (-1, 0), 1: (1, 0)}
moves = []

boundary = 0
for line in input:
    line = line.split()
    hex_code = line[2][2:-1]
    direction = int(hex_code[-1])
    steps = int(hex_code[:-1], 16)
    moves.append((direction, steps))
    boundary += steps

points = [(0, 0)]
position = [0, 0]
for move, steps in moves:
    dy, dx = directions[move]
    position[0] += steps * dy
    position[1] += steps * dx
    points.append(tuple(position))

area = 0
for i in range(1, len(points)):
    ii = i - 1
    area += (points[i][1] + points[ii][1]) * (points[i][0] - points[ii][0])
area /= 2

interior = area - (boundary / 2) + 1
print(interior + boundary)