import os
import sys

__location__ = os.path.join(sys.path[0], 'inputs/i2.txt')

reports = []
with open(__location__, 'r') as file:
    for line in file: 
        report = line.strip().split()
        reports.append(report)

def checkSafe(list) -> bool:
    increasing = False
    decreasing = False
    for i in range(len(list)-1):
        level1 = int(list[i])
        level2 = int(list[i+1])

        if (level1 < level2):
            increasing = True
        if (level1 > level2):
            decreasing = True
        if (increasing and decreasing):
            return False
        diff = abs(level1 - level2)
        if (diff < 1 or diff > 3):
            return False
    return True


n = len(reports)
safeCt = 0
for report in reports:
    for i in range(len(report)):
        listWithouti = report.copy()
        listWithouti.pop(i)
        if checkSafe(listWithouti):
            print("safe list is ", listWithouti)
            safeCt += 1
            break
print("safe count is ", safeCt)