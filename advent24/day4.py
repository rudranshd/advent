import os
import sys

EXPECTED_STRING = " .XMAS"
DIRECTIONS = {
    'N': (-1, 0),
    'NE': (-1, 1),
    'E': (0, 1),
    'SE': (1, 1),
    'S': (1, 0),
    'SW': (1, -1),
    'W': (0, -1),
    'NW': (-1, -1),
}

__location__ = os.path.join(sys.path[0], 'inputs/i4.txt')

def recur1(input, i, j, direction):
    drow, dcol = DIRECTIONS[direction]
    next_row, next_col = i + drow, j + dcol

    if not (0 <= next_row < len(input) and 0 <= next_col < len(input[0])):
        return 0

    currChar = input[i][j]
    nextChar = input[next_row][next_col]

    # recursive base case
    if currChar == 'S':
        return 1
    
    if EXPECTED_STRING.index(currChar) == EXPECTED_STRING.index(nextChar)-1:
        return recur1(input, next_row, next_col, direction)
    else:
        return 0

def recur2(input, i, j):
    NE_char = input[i-1][j+1]
    SE_char = input[i+1][j+1]
    SW_char = input[i+1][j-1]
    NW_char = input[i-1][j-1]
    if NE_char == 'M' and SW_char == 'S' and NW_char == 'M' and SE_char == 'S':
        # print("i: ", i, "j: ", j)
        return 1
    elif NE_char == 'M' and SW_char == 'S' and NW_char == 'S' and SE_char == 'M':
        # print("i: ", i, "j: ", j)
        return 1
    elif NE_char == 'S' and SW_char == 'M' and NW_char == 'S' and SE_char == 'M':
        # print("i: ", i, "j: ", j)
        return 1
    elif NE_char == 'S' and SW_char == 'M' and NW_char == 'M' and SE_char == 'S':
        # print("i: ", i, "j: ", j)
        return 1    
    else:
        return 0

input = []
width = 0
with open(__location__, 'r') as file:
    for line in file:
        toAppend = [' '] + list(line)[:len(line)-1] + [' ']
        input.append(toAppend)
        width = len(line)+1

input = [list('.'*width)] + input + [list('.'*width)]

xmas_count = 0
for i in range(1, len(input)):
    for j in range(1, len(input[i])):
        if input[i][j] == 'X':
            for direction in DIRECTIONS:
                xmas_count += recur1(input, i, j, direction)

print("part 1 xmas_count is: ", xmas_count)

xmas_count = 0
for i in range(1, len(input)):
    for j in range(1, len(input[i])):
        if input[i][j] == 'A':
            xmas_count += recur2(input, i, j)

print("part 2 xmas_count is: ", xmas_count)