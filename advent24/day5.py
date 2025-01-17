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
incorrectly_ordered_updates = []
sum_middles_correct = 0
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
        sum_middles_correct += update[len(update) // 2]
    else:
        incorrectly_ordered_updates.append(update)

swapped = False
for update in incorrectly_ordered_updates:
    backwards_seen_page_set.clear()
    update_set = set(update)
    i = len(update) - 1
    while i > 0:
        swapped = False
        current_page = update[i]
        needs_to_be_seen = ordering_rules[current_page]
        for page in needs_to_be_seen:
            if page not in backwards_seen_page_set and page in update_set:
                a, b, = i, update.index(page)
                update[a], update[b] = update[b], update[a]
                backwards_seen_page_set.clear()
                swapped = True
                break
        if not swapped:
            backwards_seen_page_set.add(current_page)
        if swapped:
            i = len(update)
        i -= 1

sum_middles_incorrect = 0
for incorrectly_ordered_update in incorrectly_ordered_updates:
    sum_middles_incorrect += incorrectly_ordered_update[len(incorrectly_ordered_update) // 2]

print("sum middles correct is ", sum_middles_correct)
print("sum middles incorrect is ", sum_middles_incorrect)
