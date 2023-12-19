from functools import reduce

input = open('input2.txt').read().splitlines()

workflows = { 'A': [], 'R': []}
point_map = {'x': 0, 'm': 1, 'a': 2, 's' : 3}

for line in input:
    if line == '':
        break
    workflow = line[:-1].split('{')
    workflow_name = workflow[0]
    steps = workflow[1].split(',')
    steps_lst = []
    for step in steps:
        condition_redirection = step.split(':')
        if len(condition_redirection) == 1:
            steps_lst.append(condition_redirection)
        else:
            num = int(condition_redirection[0][2:])
            point = point_map[condition_redirection[0][0]]
            steps_lst.append((point, condition_redirection[0][1], num, condition_redirection[1]))
    workflows[workflow_name] = steps_lst

def combinations_count(ranges, workflow):
    if workflow == 'R':
        return 0
    if workflow == 'A':
        return reduce(lambda x, y: x * (y[1] - y[0] + 1), ranges, 1)

    steps = workflows[workflow]
    result = 0
    for step in steps:
        if len(step) == 1:
            result += combinations_count(ranges, step[0])
            break
        
        point = step[0]
        l, h = ranges[point]
        if step[1] == '>':
            happy_path = (step[2] + 1, h)
            sad_path = (l, step[2])
        else:
            happy_path = (l, step[2] - 1)
            sad_path = (step[2], h)
        
        if happy_path[0] <= happy_path[1]:
            ranges_copy = list(ranges)
            ranges_copy[point] = happy_path
            result += combinations_count(ranges_copy, step[3])
        
        if sad_path[0] <= sad_path[1]:
            ranges = list(ranges)
            ranges[point] = sad_path
        else:
            break
    return result

print(combinations_count([(1, 4000), (1, 4000), (1, 4000), (1, 4000)], 'in'))