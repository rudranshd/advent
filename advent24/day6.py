import os
import sys
from datetime import datetime

start_time = datetime.now()

sys.setrecursionlimit(10000)
max_recursion_depth = 0

DIRECTION_ORDER = ['N', 'E', 'S', 'W']
DIRECTIONS = {
    'N': (-1, 0),
    'E': (0, 1),
    'S': (1, 0),
    'W': (0, -1)
}

__location__ = os.path.join(sys.path[0], 'inputs/i6.txt')

map = [list(line.strip()) for line in open(__location__, 'r')]

def print_map(map):
    for line in map:
        print(*line)

def get_next_dir(dir):
    return DIRECTION_ORDER[(DIRECTION_ORDER.index(dir) + 1) % 4]

def get_start(mp):
    for i in range(len(mp)):
        for j in range(len(mp[0])):
            if mp[i][j] == '^':
                return (i, j)
            
def check_bounds(i, j, map):
    return i >= 0 and i < len(map) and j >= 0 and j < len(map[0])

def get_number_positions_visited(map):
    count = 0
    for line in map:
        for char in line:
            if char == 'X':
                count += 1
    return count

def recur(i, j, dir, map, recursion_depth=0):
    """Recursively tries to exit graph, keeping track of the number of calls to the stack. """
    recursion_depth += 1
    map[i][j] = 'X'

    ni, nj = i + DIRECTIONS[dir][0], j + DIRECTIONS[dir][1]
    if not check_bounds(ni, nj, map):
        global max_recursion_depth
        max_recursion_depth = recursion_depth
        return

    if map[ni][nj] == '#':
        recur(i, j, get_next_dir(dir), map, recursion_depth)
    else:
        recur(i + DIRECTIONS[dir][0], j + DIRECTIONS[dir][1], dir, map, recursion_depth)

def is_there_loop_with_recursive_depth(i, j, dir, map, recursion_depth = 0):
    """Recursively checks for loop, terminating if the number of calls far exceeds the iterations required to exit the graph. """
    recursion_depth += 1
    map[i][j] = 'X'

    """386 extra calls are required to detect loop in the input. The original guess was 100, then 1000, then narrowed down from there. """
    if recursion_depth > max_recursion_depth + 386:
        return True
    
    ni, nj = i + DIRECTIONS[dir][0], j + DIRECTIONS[dir][1]
    if not check_bounds(ni, nj, map):
        return False
    
    if map[ni][nj] == '#' or map[ni][nj] == 'O':
        return is_there_loop_with_recursive_depth(i, j, get_next_dir(dir), map, recursion_depth)
    else:
        return is_there_loop_with_recursive_depth(ni, nj, dir, map, recursion_depth)

def is_there_loop_with_visited_set(i, j, dir, visited, map):
    """Recursively checks for loop using tuple-set of visited positions. """
    visited.add((i, j, dir))
    ni, nj = i + DIRECTIONS[dir][0], j + DIRECTIONS[dir][1]
    if not check_bounds(ni, nj, map):
        return False

    if (ni, nj, dir) in visited:
        return True

    if map[ni][nj] == '#' or map[ni][nj] == 'O':
        return is_there_loop_with_visited_set(i, j, get_next_dir(dir), visited, map)
    else:
        return is_there_loop_with_visited_set(ni, nj, dir, visited, map)

print("Before recursion")   
print_map(map)
print()

starting_point = get_start(map)
result = recur(starting_point[0], starting_point[1], 'N', map)
end_time = datetime.now()

print("After recursion")
print_map(map)
print("Total positions visited: ", get_number_positions_visited(map))
print("Max recursion depth: ", max_recursion_depth)
print('Part 1 runtime: {}'.format(end_time - start_time))

# Part 2

start_time = datetime.now()
visited_set_obstruction_count = 0
recursion_depth_obstruction_count = 0
visited_positions = set()
print()
"""HUGE optimization is to only check for obstacles in the original path of the guard as opposed to every possible postion. """
for i in range(len(map)):
    for j in range(len(map[0])):
        if map[i][j] == 'X':
            new_map = [line.copy() for line in map]
            new_map[i][j] = 'O'
            visited_positions.clear()
            if is_there_loop_with_visited_set(starting_point[0], starting_point[1], 'N', visited_positions, new_map):
                visited_set_obstruction_count += 1
end_time = datetime.now()

print("Possible obstruction count using visited set:     ", visited_set_obstruction_count)
print('Visited set impl runtime:     {}'.format(end_time - start_time))
"""Runtime is: 0:00:05.774249"""

start_time = datetime.now()
for i in range(len(map)):
    for j in range(len(map[0])):
        if map[i][j] == 'X':
            new_map = [line.copy() for line in map]
            new_map[i][j] = 'O'
            if is_there_loop_with_recursive_depth(starting_point[0], starting_point[1], 'N', new_map):
                recursion_depth_obstruction_count += 1
end_time = datetime.now()

print("Possible obstruction count using recursion depth: ", recursion_depth_obstruction_count)
print('Recursion depth impl runtime: {}'.format(end_time - start_time))
"""Runtime is 0:00:05.123404"""
