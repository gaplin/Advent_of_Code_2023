input = open("input/input.txt", "r").read().split(',')

result = 0
for text in input:
    hash = 0
    for char in text:
        hash += ord(char)
        hash *= 17
        hash %= 256
    result += hash

print(result)