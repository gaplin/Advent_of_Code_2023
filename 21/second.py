from queue import Queue

def num_of_covered_points(grid, starting_position, limit, n, parity):
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    visited = set()
    q = Queue()
    q.put((0, starting_position[0], starting_position[1]))
    visited.add(starting_position)
    result = 0

    while q.empty() == False:
        distance, i, ii = q.get()
        if distance % 2 == parity:
            result += 1
        if distance == limit:
            continue

        for di, dii in directions:
            new_i, new_ii = i + di, ii + dii
            if new_i < 0 or new_i >= n or new_ii < 0 or new_ii >= n \
            or (new_i, new_ii) in visited or grid[new_i][new_ii] == '#':
                continue
            visited.add((new_i, new_ii))
            q.put((distance + 1, new_i, new_ii))
    
    return result

result = 0
limit = 26501365
grid = open('input2.txt').read().splitlines()
n = len(grid)
starting_position = (n // 2, n // 2)
r = limit // n - 1
odd_grids = r ** 2
even_grids = (r + 1) ** 2
odd_points = num_of_covered_points(grid, (starting_position[0], starting_position[1]), n * 2, n, 1)
even_points = num_of_covered_points(grid, (starting_position[0], starting_position[1]), n * 2, n, 0)
result += even_grids * even_points + odd_grids * odd_points

top = num_of_covered_points(grid, (n - 1, starting_position[1]), n - 1, n, 0)
down = num_of_covered_points(grid, (0, starting_position[1]), n - 1, n, 0)
right = num_of_covered_points(grid, (starting_position[0], 0), n - 1, n, 0)
left = num_of_covered_points(grid, (starting_position[0], n - 1), n - 1, n, 0)
result += top + down + right + left

tr_sticking_out = num_of_covered_points(grid, (n - 1, 0), n // 2 - 1, n, 0)
tl_sticking_out = num_of_covered_points(grid, (n - 1, n - 1), n // 2 - 1, n, 0)
br_sticking_out = num_of_covered_points(grid, (0, 0), n // 2 - 1, n, 0)
bl_sticking_out = num_of_covered_points(grid, (0, n - 1), n // 2 - 1, n, 0)
result += (r + 1) * (tr_sticking_out + tl_sticking_out + br_sticking_out + bl_sticking_out)

tr_partially_covered = num_of_covered_points(grid, (n - 1, 0), n + n // 2 - 1, n, 1)
tl_partially_covered = num_of_covered_points(grid, (n - 1, n - 1), n + n // 2 - 1, n, 1)
br_partially_covered = num_of_covered_points(grid, (0, 0), n + n // 2 - 1, n, 1)
bl_partially_covered = num_of_covered_points(grid, (0, n - 1), n + n // 2 - 1, n, 1)
result += r * (tr_partially_covered + tl_partially_covered + br_partially_covered + bl_partially_covered)

print(result)

