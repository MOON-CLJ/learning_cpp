import random

l = [(i, j) for i in range(4) for j in range(13)]
print len(l)
random.shuffle(l)

h = 1
while (h < len(l) / 3):
    h = 3 * h + 1
print h

while (h >= 4):
    for i in range(h, len(l)):
        j = i
        while j >= h and (l[j][0] < l[j - h][0] or
                          (l[j][0] == l[j - h][0] and l[j][1] < l[j - h][1])):
            tmp = l[j]
            l[j] = l[j - h]
            l[j - h] = tmp
            j -= h
    h /= 3

for i in l:
    print i
