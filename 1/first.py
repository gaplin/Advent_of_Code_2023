input = open("input/input.txt", "r").read().splitlines()

sum = 0 

for value in input: 
    digits = ''
    for char in value:
        if char.isdigit():
            digits += char
            break
    for char in reversed(value):
        if char.isdigit():
            digits += char
            break
    sum += int(digits)

print(sum)