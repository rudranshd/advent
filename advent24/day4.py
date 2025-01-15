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

def recur(input, i, j, direction):  
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
        return recur(input, next_row, next_col, direction)
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
                xmas_count += recur(input, i, j, direction)

print("xmas_count is: ", xmas_count)

