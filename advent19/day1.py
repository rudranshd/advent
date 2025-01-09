
import math

sum = 0
currSum = 0
curr = 555
with open ("/mnt/c/Users/Rudy/Documents/advent/advent19/inputs/i1.txt") as fp: 
    for line in fp: 
        currSum = 0
        curr = float(line)
        while True: 
            curr = (math.floor(curr/3))-2
            if (curr <= 0):
                break
            currSum += curr
        sum += currSum
        print("the sum now is " + str(sum))

print (sum)