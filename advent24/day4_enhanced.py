import os
import sys
from itertools import permutations

EXPECTED_STRING = " .XMAS"

__location__ = os.path.join(sys.path[0], 'inputs/i4.txt')

def is_xmas(input, i, j):
    """Checks if the given position is the center of a valid 'XMAS' pattern."""
    neighbors = [
        input[i-1][j+1],  # NE
        input[i+1][j+1],  # SE
        input[i+1][j-1],  # SW
        input[i-1][j-1]   # NW
    ]

    # More elegant check using set operations
    if (neighbors[0] in ('M', 'S') and neighbors[2] in ('M', 'S') and
        neighbors[1] in ('M', 'S') and neighbors[3] in ('M', 'S') and
        {neighbors[0], neighbors[2]} == {'M', 'S'} and
        {neighbors[1], neighbors[3]} == {'M', 'S'}):
        return True
    return False

def count_xmas(input_lines):
    """Counts the number of 'XMAS' patterns in the input."""
    width = len(input_lines[0])
    #Pad the input with '.' for boundary checks
    padded_input = [list('.' * width)] + input_lines + [list('.' * width)]

    xmas_count = 0
    for i in range(1, len(padded_input) - 1):
        for j in range(1, len(padded_input[i]) - 1):
            if padded_input[i][j] == 'A':
                if is_xmas(padded_input, i, j):
                    xmas_count += 1
    return xmas_count

def load_input(filepath):
    """Loads and preprocesses the input from the given file."""
    input_lines = []
    with open(filepath, 'r') as file:
        for line in file:
            to_append = [' '] + list(line.rstrip()) + [' '] #rstrip to remove trailing newline
            input_lines.append(to_append)
    return input_lines

if __name__ == "__main__":
    input_lines = load_input(__location__)
    xmas_count = count_xmas(input_lines)
    print("part 2 xmas_count is: ", xmas_count)
