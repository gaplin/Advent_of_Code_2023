input = open("input/input.txt", "r").read().splitlines()

def getFirstDigit(input):
    digits = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    first_digit_position = len(input)
    result = 0
    for idx, digit in enumerate(digits):
        first_occurrence = input.find(digit)
        if first_occurrence != -1 and first_occurrence < first_digit_position:
            first_digit_position = first_occurrence
            result = idx % 10
    return result

def getLastDigit(input):
    digits = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    last_digit_position = -1
    result = 0
    for idx, digit in enumerate(digits):
        last_occurrence = input.rfind(digit)
        if last_occurrence > last_digit_position:
            last_digit_position = last_occurrence
            result = idx % 10
    return result

sum = 0 

for value in input: 
    first_digit = getFirstDigit(value)
    second_digit = getLastDigit(value)
    number = first_digit * 10 + second_digit
    sum += number

print(sum)