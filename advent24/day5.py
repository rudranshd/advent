import os
import sys
from collections import defaultdict

__location__ = os.path.join(sys.path[0], 'inputs/i5.txt')

ordering_rules = defaultdict(list)
updates = []
with open(__location__, 'r') as file:
    for line in file:
        if line == "\n":
            break
        line = line.strip().split("|")
        X, Y = int(line[0]), int(line[1])
        ordering_rules[X].append(Y)
    for line in file: 
        line = line.strip().split(",")
        update = [int(x) for x in line]
        updates.append(update)

backwards_seen_page_set = set()

correctly_ordered_updates = []
sum_middles = 0
for update in updates:
    correct_order = True
    backwards_seen_page_set.clear()
    update_set = set(update)
    for i in reversed(update):
        current_page = i
        needs_to_be_seen = ordering_rules[current_page]
        for page in needs_to_be_seen:
            if page not in backwards_seen_page_set and page in update_set:
                correct_order = False
                break
        backwards_seen_page_set.add(current_page)
    if correct_order:
        correctly_ordered_updates.append(update)
        sum_middles += update[len(update) // 2]

print(correctly_ordered_updates)
print(sum_middles)
