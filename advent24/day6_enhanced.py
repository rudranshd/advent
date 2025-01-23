import os
import sys
from datetime import datetime
import multiprocessing

start_time = datetime.now()

sys.setrecursionlimit(10000)

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

def recur(i, j, dir, map):
    """Recursively tries to exit graph, keeping track of the number of calls to the stack. """
    map[i][j] = 'X'

    ni, nj = i + DIRECTIONS[dir][0], j + DIRECTIONS[dir][1]
    if not check_bounds(ni, nj, map):
        return

    if map[ni][nj] == '#':
        recur(i, j, get_next_dir(dir), map)
    else:
        recur(i + DIRECTIONS[dir][0], j + DIRECTIONS[dir][1], dir, map)

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

def check_for_loop_at_position(i, j):
    """Checks for a loop when placing an obstruction at (i, j)."""
    new_map = [line.copy() for line in map]
    new_map[i][j] = 'O'
    visited_positions = set()
    if is_there_loop_with_visited_set(starting_point[0], starting_point[1], 'N', visited_positions, new_map):
        return 1 # Loop found
    return 0 # No loop found

print("Before recursion")   
print_map(map)
print()

starting_point = get_start(map)
result = recur(starting_point[0], starting_point[1], 'N', map)
end_time = datetime.now()

print("After recursion")
print_map(map)
print("Total positions visited: ", get_number_positions_visited(map))
print('Duration: {}'.format(end_time - start_time))

# Part 2

start_time = datetime.now()
visited_set_obstruction_count = 0
print()

"""
multiprocessing.Pool: This creates a pool of worker processes. multiprocessing.cpu_count() automatically determines 
the number of CPUs available and uses them all. You can adjust this number if needed (e.g., processes=4 for 4 processes).

pool.apply_async: This submits the check_for_loop_at_position function to the pool for asynchronous execution. This means 
the main process doesn't wait for each function to complete before submitting the next one. The args tuple provides the arguments to the function.

Collecting Results: The results list stores AsyncResult objects. You need to call .get() on each result to retrieve the 
return value (0 or 1). This is done in a separate loop after all tasks have been submitted to the pool.

"""

with multiprocessing.Pool(processes=multiprocessing.cpu_count()) as pool: # Use all available CPUs
    results = [pool.apply_async(check_for_loop_at_position, args=(i, j))
                for i in range(len(map))
                for j in range(len(map[0]))
                if map[i][j] == 'X']
    for result in results:
        visited_set_obstruction_count += result.get()
end_time = datetime.now()

print("Possible obstruction count using visited set: ", visited_set_obstruction_count)
print('Parallelized visited set impl runtime: {}'.format(end_time - start_time))
"""Runtime is 0:00:00.995804"""