from queue import Queue

input = open('input/input.txt', 'r').read().splitlines()

n = len(input)
m = len(input[0])

directions = { 'R': (0, 1), 'L': (0, -1), 'U': (-1, 0), 'D': (1, 0)}

def not_visited_position(position):
    return position[0] >= 0 and position[0] < n and position[1] >= 0 and position[1] < m and position[2] not in visits[position[0]][position[1]]

def ray_traverse(i, j, direction, visits):
    q = Queue()
    visited_positions = set()
    def q_append(position):
        q.put(position)
        visited_positions.add((position[0], position[1]))
        visits[position[0]][position[1]].append(position[2])

    q_append((i, j, direction))

    while q.empty() == False:
        position = q.get()
        step = directions[position[2]]

        if input[position[0]][position[1]] == '.':
            new_position = (position[0] + step[0], position[1] + step[1], position[2])
            if not_visited_position(new_position):
                q_append(new_position)
            continue
        
        if input[position[0]][position[1]] == '|':
            if position[2] == 'R' or position[2] == 'L':
                new_position = (position[0] - 1, position[1], 'U')
                if not_visited_position(new_position):
                    q_append(new_position)

                new_position = (position[0] + 1, position[1], 'D')
                if not_visited_position(new_position):
                    q_append(new_position)
                continue
            
            new_position = (position[0] + step[0], position[1] + step[1], position[2])
            if not_visited_position(new_position):
                q_append(new_position)
            continue
        
        if input[position[0]][position[1]] == '-':
            if position[2] == 'U' or position[2] == 'D':
                new_position = (position[0], position[1] + 1, 'R')
                if not_visited_position(new_position):
                    q_append(new_position)

                new_position = (position[0], position[1] - 1, 'L')
                if not_visited_position(new_position):
                    q_append(new_position)
                continue
            
            new_position = (position[0] + step[0], position[1] + step[1], position[2])
            if not_visited_position(new_position):
                q_append(new_position)
            continue
        
        if input[position[0]][position[1]] == '/':
            if position[2] == 'R':
                new_position = (position[0] - 1, position[1], 'U')
                if not_visited_position(new_position):
                    q_append(new_position)
            elif position[2] == 'L':
                new_position = (position[0] + 1, position[1], 'D')
                if not_visited_position(new_position):
                    q_append(new_position)
            elif position[2] == 'U':
                new_position = (position[0], position[1] + 1, 'R')
                if not_visited_position(new_position):
                    q_append(new_position)
            else:
                new_position = (position[0], position[1] - 1, 'L')
                if not_visited_position(new_position):
                    q_append(new_position)
            continue
        
        if input[position[0]][position[1]] == '\\':
            if position[2] == 'R':
                new_position = (position[0] + 1, position[1], 'D')
                if not_visited_position(new_position):
                    q_append(new_position)
            elif position[2] == 'L':
                new_position = (position[0] - 1, position[1], 'U')
                if not_visited_position(new_position):
                    q_append(new_position)
            elif position[2] == 'U':
                new_position = (position[0], position[1] - 1, 'L')
                if not_visited_position(new_position):
                    q_append(new_position)
            else:
                new_position = (position[0], position[1] + 1, 'R')
                if not_visited_position(new_position):
                    q_append(new_position)
    return len(visited_positions)

result = 0
for i in range(n):
    visits = [[[] for _ in range(m)] for _ in range(n)]
    result = max(result, ray_traverse(i, 0, 'R', visits))
    visits = [[[] for _ in range(m)] for _ in range(n)]
    result = max(result, ray_traverse(i, m - 1, 'L', visits))

for i in range(m):
    visits = [[[] for _ in range(m)] for _ in range(n)]
    result = max(result, ray_traverse(0, i, 'D', visits))
    visits = [[[] for _ in range(m)] for _ in range(n)]
    result = max(result, ray_traverse(n - 1, i, 'U', visits))

print(result)