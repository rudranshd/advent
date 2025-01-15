import re
import os
import sys

__location__ = os.path.join(sys.path[0], 'inputs/i3.txt')

def parse_instruction(instruction):
    """Parses the instruction and returns relevant data."""
    if instruction == "do()":
        return "do", None
    elif instruction == "don't()":
        return "dont", None
    else:
        match = re.match("mul\\((\\d+),(\\d+)\\)", instruction)
        if match:
            return "mul", [int(group) for group in match.groups()]
        return "invalid", None  # Handle invalid instructions gracefully


def process_instructions(instructions):
    """Processes instructions and calculates the sum, handling do()/don't().
    This implementation was enhanced with the help of Gemini 2.0. At first, it did
    not recognize that when a don't instruction is encountered, parsing should be
    paused until a do instruction is encountered. 
    """
    total_sum = 0
    parsing_enabled = True

    for instruction in instructions:
        action, numbers = parse_instruction(instruction)

        if action == "do":
            parsing_enabled = True
            continue  # Important: Skip to the next instruction
        elif action == "dont":
            parsing_enabled = False
            continue  # Important: Skip to the next instruction
        elif action == "mul" and parsing_enabled:
            product = 1
            for num in numbers:
                product *= num
            total_sum += product
        elif action == "invalid":
            print(f"Warning: Invalid instruction '{instruction}' encountered. Skipping.")

    return total_sum

# Load instructions from a file (optional for flexibility)
def load_instructions_from_file(filename):
    """Loads instructions from a specified file.

    Args:
        filename (str): The filename.

    Returns:
        list[str]: The list of instructions loaded from the file.
    """

    with open(filename, 'r') as file:
        memory = file.read()
    return re.findall("mul\\(\\d+,\\d+\\)|do\\(\\)|don\\'t\\(\\)", memory)

# Example usage with loaded instructions
instructions = load_instructions_from_file(__location__)
sum = process_instructions(instructions)
print(sum)
