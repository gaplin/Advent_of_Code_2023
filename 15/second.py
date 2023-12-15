input = open("input/input.txt", "r").read().split(',')

buckets = [[] for _ in range(0, 256)]
for text in input:
    hash = 0
    separator_idx = 0
    for idx, char in enumerate(text):
        if char == '-' or char == '=':
            separator_idx = idx
            break
        hash += ord(char)
        hash *= 17
        hash %= 256
    text_value = (text[:separator_idx], text[separator_idx + 1:])
    value_processed = False
    for idx, code_value in enumerate(buckets[hash]):
        if code_value[0] == text_value[0]:
            value_processed = True
            if text[separator_idx] == '-':
                del buckets[hash][idx]
            else:
                buckets[hash][idx] = text_value
            break
    if value_processed == False and text[separator_idx] == '=':
        buckets[hash].append(text_value)

result = 0
for i, focals in enumerate(buckets):
    for ii, focal in enumerate(focals):
        result += (i + 1) * (ii + 1) * int(focal[1])

print(result)