input = open('input2.txt').read().splitlines()
n = len(input)
hailstones = []

for line in input:
    line = line.split(' @ ')
    point = list(map(float, line[0].split(', ')))
    direction = list(map(float, line[1].split(', ')))
    hailstones.append((point, direction))

def get_line(x1, y1, x2, y2):
    if x1 == x2:
        return (1, 0, -x1)
    
    a = (y2 - y1) / (x2 - x1)
    b = y1 - a * x1
    return (-a, 1, -b)

def get_intersection(A, B):
    if A[0] == B[0]:
        raise Exception('parallel lines')
    
    x = (B[2] - A[2]) / (A[0] - B[0])
    y = -A[0] * x - A[2]

    return (x, y)

def intersection_in_future(hailstone, x, y):
    vec = [x - hailstone[0][0], y - hailstone[0][1]]
    return vec[0] * hailstone[1][0] >= 0 and vec[1] * hailstone[1][1] >= 0

lines = []

for stone in hailstones:
    lines.append(get_line(stone[0][0], stone[0][1], stone[0][0] + stone[1][0], stone[0][1] + stone[1][1]))

low = 200000000000000
high = 400000000000000
result = 0
result = 0
for i in range(n - 1):
    for j in range(i + 1, n):
        if lines[i][0] != lines[j][0]:
            x, y = get_intersection(lines[i], lines[j])
            if intersection_in_future(hailstones[i], x, y) and intersection_in_future(hailstones[j], x, y) and low <= x <= high and low <= y <= high:
                result += 1

print(result)