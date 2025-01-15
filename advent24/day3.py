import re
import os
import sys

__location__ = os.path.join(sys.path[0], 'inputs/i3_read1.txt')

memory = ""
with open(__location__, 'r') as file:
    memory = file.read()

# read in mul(\d, \d) OR do() OR don't()
mul_instructions = re.findall("mul\\(\\d+,\\d+\\)|do\\(\\)|don\\'t\\(\\)", memory)

sum = 0
continue_parsing = True
for instruction in mul_instructions:
    if instruction == "do()":
        continue_parsing = True
    elif instruction == "don't()":
        continue_parsing = False
    elif continue_parsing:
        nums = re.findall("\\d+", instruction)
        prod = 1
        for num in nums:
            prod *= int(num)
        sum += prod

print(sum)
    