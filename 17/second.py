from queue import Queue

input = open('input/input.txt', 'r').read().splitlines()
input = [[int(cell) for cell in line] for line in input]
n = len(input)
m = len(input[0])
distances = [[2000000000 for _ in range(m)] for _ in range(n)]
directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

S = (0, 0)
E = (n - 1, m - 1)
distances[S[0]][S[1]] = 0
q = Queue()
q.put((0, 0, (0, 0), 0))
visits = {}
visits[(0, 0, (0, 0), 0)] = 0

while q.empty() == False:
    i, j, from_direction, steps = q.get()
    to_direction = (from_direction[0] * -1, from_direction[1] * -1)
    for direction in directions:
        next_i = i
        next_j = j
        new_distance = visits[(i, j, from_direction, steps)]
        if direction == from_direction:
            continue
        if direction == to_direction:
            if steps == 10:
                continue

            next_i += direction[0]
            next_j += direction[1]
            if next_i < 0 or next_i >= n or next_j < 0 or next_j >= m:
                continue
            new_steps = steps + 1
            
            new_distance += input[next_i][next_j]
            v_tuple = (next_i, next_j, (-direction[0], -direction[1]), new_steps)
            if v_tuple in visits:
                if new_distance < visits[v_tuple]:
                    visits[v_tuple] = new_distance
                    q.put(v_tuple)
            else:
                q.put(v_tuple)
                visits[v_tuple] = new_distance

            if new_distance < distances[next_i][next_j]:
                distances[next_i][next_j] = new_distance
            continue

        valid_move = True
        for _ in range(4):
            next_i += direction[0]
            next_j += direction[1]
            if next_i < 0 or next_i >= n or next_j < 0 or next_j >= m:
                valid_move = False
                break
            new_distance += input[next_i][next_j]
        
        if valid_move == False:
            continue

        v_tuple = (next_i, next_j, (-direction[0], -direction[1]), 4)
        if v_tuple in visits:
            if new_distance < visits[v_tuple]:
                    visits[v_tuple] = new_distance
                    q.put(v_tuple)
        else:
            q.put(v_tuple)
            visits[v_tuple] = new_distance

        if new_distance < distances[next_i][next_j]:
            distances[next_i][next_j] = new_distance

print(distances[E[0]][E[1]])