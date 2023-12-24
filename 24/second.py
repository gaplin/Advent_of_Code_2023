import sympy
input = open('input2.txt').read().splitlines()
n = len(input)
hailstones = []

for line in input:
    line = line.split(' @ ')
    point = list(map(float, line[0].split(', ')))
    direction = list(map(float, line[1].split(', ')))
    hailstones.append((*point, *direction))

x, y, z, vx, vy, vz = sympy.symbols("x, y, z, vx, vy, vz")
equations = []
for i, (hx, hy, hz, tx, ty, tz) in enumerate(hailstones):
    equations.append((x - hx) * (ty - vy) - (y - hy) * (tx - vx))
    equations.append((y - hy) * (tz - vz) - (z - hz) * (ty - vy))
    if i < 3:
        continue
    solutions = sympy.solve(equations)
    for solution in solutions:
        all_integers = True
        for value in solution.values():
            if value % 1 != 0:
                all_integers = False
        if all_integers == True:
            print(int(solution[x] + solution[y] + solution[z]))
            exit()
