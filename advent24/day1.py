import os
import sys
import heapq

__location__ = os.path.join(sys.path[0], 'inputs/i1.txt')

heap1 = []
heap2 = []

a1 = []
dict = {}

with open(__location__, 'r') as file:
    lines = file.readlines()
    for line in lines:
        parts = line.strip().split()
        a1.append(int(parts[0]))

        dict[int(parts[1])] = dict.get(int(parts[1]), 0) + 1
        
        heapq.heappush(heap1, int(parts[0]))
        heapq.heappush(heap2, int(parts[1]))

size = len(heap1)
sum1 = 0
sim_score = 0
for i in range(size):
    n1 = heapq.heappop(heap1)
    n2 = heapq.heappop(heap2)
    diff = abs(n1 - n2)
    sum1 += diff

    sim_score += a1[i] * dict.get(a1[i], 0)

print(sum1)
print(sim_score)
        