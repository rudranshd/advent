list = []

with open ("/mnt/c/Users/Rudy/Documents/advent/advent19/inputs/i2.txt") as f: 
    for line in f: 
        list.append(line.split(','))

sum = 0
for num in list[0]: 
    sum += int(num)

print("the sum of nums is: " + str(sum))
print(list[0])

