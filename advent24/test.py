import os
import sys

INPUT_FILE = os.path.join(sys.path[0], 'inputs/i2.txt')

def is_safe(levels):
    """Checks if a list of levels is safe."""
    for i in range(len(levels) - 1):
        diff = abs(levels[i] - levels[i + 1])
        if not (1 <= diff <= 3):
            return False
    return True

def process_reports(filepath):
    """Processes reports and counts safe reports after removal."""
    safe_count = 0
    with open(filepath, 'r') as file:
        for line in file:
            report_strings = line.strip().split()
            report = [int(x) for x in report_strings]
            n = len(report)

            for i in range(n):
                temp_report = report[:i] + report[i+1:]
                if is_safe(temp_report):
                    print("safe list is ", temp_report)
                    safe_count += 1
                    break  # Correctly placed break statement
    return safe_count

if __name__ == "__main__":
    safe_ct = process_reports(INPUT_FILE)
    print("safe count is ", safe_ct)
