from queue import Queue

input = open('input2.txt').read().splitlines()
def non_empty_intersection(brick_a, brick_b):
    return max(brick_a[0], brick_b[0]) <= min(brick_a[3], brick_b[3]) and max(brick_a[1], brick_b[1]) <= min(brick_a[4], brick_b[4])

def move_down(bricks):
    for i, brick in enumerate(bricks):
        resting_position = 1
        for j in range(0, i):
            if non_empty_intersection(brick, bricks[j]):
                resting_position = max(resting_position, bricks[j][5] + 1)
        brick[5] -= brick[2] - resting_position
        brick[2] = resting_position


bricks = []
for line in input:
    points = line.split('~')
    bottom_left = map(int, points[0].split(','))
    top_right = map(int, points[1].split(','))
    bricks.append([*bottom_left, *top_right])

n = len(bricks)
bricks.sort(key=lambda x: x[2])

move_down(bricks)
bricks.sort(key=lambda x: x[2])
ons = {i: set() for i in range(n)}
unders = {i: set() for i in range(n)}

for i in range(n):
    for j in range(0, i):
        if non_empty_intersection(bricks[i], bricks[j]) == True and bricks[i][2] - 1 == bricks[j][5]:
            unders[i].add(j)
            ons[j].add(i)

result = 0
for i in range(n):
    q = Queue()
    falling = set()
    q.put(i)
    falling.add(i)
    while q.empty() == False:
        j = q.get()
        for on in ons[j]:
            if on not in falling and unders[on] <= falling:
                falling.add(on)
                q.put(on)

    result += len(falling) - 1

print(result)