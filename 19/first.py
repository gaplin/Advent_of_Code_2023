input = open('input2.txt').read().splitlines()

workflows = { 'A': [], 'R': []}
items = []
point_map = {'x': 0, 'm': 1, 'a': 2, 's' : 3}

item_start = False
for line in input:
    if item_start == False:
        if line == '':
            item_start = True
            continue
        workflow = line[:-1].split('{')
        workflow_name = workflow[0]
        steps = workflow[1].split(',')
        steps_lst = []
        for step in steps:
            condition_redirection = step.split(':')
            if len(condition_redirection) == 1:
                steps_lst.append(lambda x, y = condition_redirection[0] : y)
            else:
                num = int(condition_redirection[0][2:])
                point = point_map[condition_redirection[0][0]]
                if condition_redirection[0][1] == '>':
                    steps_lst.append(lambda x, y = point, z = num, r = condition_redirection[1] : r if x[y] > z else False)
                else:
                    steps_lst.append(lambda x, y = point, z = num, r = condition_redirection[1] : r if x[y] < z else False)
        workflows[workflow_name] = steps_lst
    else:
        item = line[1:-1].split(',')
        new_item = []
        for point in item:
            value = int(point.split('=')[1])
            new_item.append(value)
        items.append(new_item)

rating = 0
for item in items:
    current_workflow = 'in'
    while current_workflow != 'A' and current_workflow != 'R':
        for step in workflows[current_workflow]:
            result = step(item)
            if result != False:
                current_workflow = result
                break
    if current_workflow == 'A':
        rating += item[0] + item[1] + item[2] + item[3]

print(rating)
