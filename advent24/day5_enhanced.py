import os
import sys
from collections import defaultdict

def solve_ordering(input_path):
    """Solves the page ordering problem from the given input file."""

    ordering_rules = defaultdict(list)
    updates = []

    try:
        with open(input_path, 'r') as file:
            # Read ordering rules
            for line in file:
                line = line.strip()
                if not line:  # Check for empty lines more efficiently
                    break
                X, Y = map(int, line.split("|"))  # Use map for concise conversion
                ordering_rules[X].append(Y)

            # Read updates
            for line in file:
                updates.append(list(map(int, line.strip().split(","))))  # More efficient conversion

    except FileNotFoundError:
        return "Input file not found."
    except ValueError:
        return "Invalid input format in file."

    correctly_ordered_updates = []
    incorrectly_ordered_updates = []

    for update in updates:
        if is_correctly_ordered(update, ordering_rules):
            correctly_ordered_updates.append(update)
        else:
            incorrectly_ordered_updates.append(update)

    # Attempt to correct incorrect updates (more efficient logic)
    corrected_incorrect_updates = []
    for update in incorrectly_ordered_updates:
        corrected_update = correct_update(update, ordering_rules)
        corrected_incorrect_updates.append(corrected_update)


    sum_middles_correct = sum(update[len(update) // 2] for update in correctly_ordered_updates)
    sum_middles_incorrect = sum(update[len(update) // 2] for update in corrected_incorrect_updates)

    return sum_middles_correct, sum_middles_incorrect

def is_correctly_ordered(update, ordering_rules):
    """Checks if an update is correctly ordered."""
    seen = set()
    for current_page in reversed(update):
        for page in ordering_rules[current_page]:
            if page in update and page not in seen:
                return False
        seen.add(current_page)
    return True

def correct_update(update, ordering_rules):
    """Attempts to correct an incorrectly ordered update."""
    update = update[:] #create a copy to not modify the original list
    n = len(update)
    for i in range(n - 1, 0, -1):
        seen = set()
        for j in range(i, n):
            current_page = update[j]
            for page in ordering_rules[current_page]:
                if page in update and page not in seen and page in update[:j]:
                    k = update.index(page)
                    update[j], update[k] = update[k], update[j]
                    return correct_update(update, ordering_rules) #recursive call to ensure full correction
            seen.add(current_page)
    return update

if __name__ == "__main__":
    __location__ = os.path.join(sys.path[0], 'inputs/i5.txt')
    sum_correct, sum_incorrect = solve_ordering(__location__)
    if isinstance(sum_correct, str): #check if error message was returned
        print(sum_correct)
    else:
        print("sum middles correct is ", sum_correct)
        print("sum middles incorrect is ", sum_incorrect)
