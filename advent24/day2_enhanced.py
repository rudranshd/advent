import os
import sys

INPUT_FILE = os.path.join(sys.path[0], 'inputs/i2.txt')

def is_safe(levels):
    """Checks if a list of levels is safe based on the given criteria.

    Args:
        levels: A list of integers representing levels.

    Returns:
        True if the levels are safe, False otherwise.
    """
    increasing = False
    decreasing = False
    for i in range(len(levels) - 1):
        level1 = levels[i]
        level2 = levels[i + 1]

        if level1 < level2:
            increasing = True
        elif level1 > level2:  # Use elif for efficiency
            decreasing = True

        if increasing and decreasing:
            return False

        diff = abs(level1 - level2)
        if not (1 <= diff <= 3): # More concise range check
            return False
    return True

def process_reports(filepath):
    """Processes reports from a file and counts safe reports after removal of one element.

    Args:
        filepath: The path to the input file.

    Returns:
        The count of safe reports.
    """
    safe_count = 0
    with open(filepath, 'r') as file:
        for line in file:
            report_strings = line.strip().split()
            report = [int(x) for x in report_strings] # Convert to integers directly

            for i in range(len(report)):
                list_without_i = report[:i] + report[i+1:] # More efficient slicing
                if is_safe(list_without_i):
                    print("safe list is ", list_without_i)
                    safe_count += 1
                    break  # Only count a report once if it's safe
    return safe_count

if __name__ == "__main__": #Good practice to put main execution in a main block
    safe_ct = process_reports(INPUT_FILE)
    print("safe count is ", safe_ct)
