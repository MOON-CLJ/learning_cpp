import sys


def can_place_if(maps, x, y, count):
    if maps[x][y] == 'X':
        return False

    # x--
    for x1 in xrange(x - 1, -1, -1):
        if maps[x1][y] == 'M':
            return False
        if maps[x1][y] == 'X':
            break
    # x++
    for x1 in xrange(x + 1, count):
        if maps[x1][y] == 'M':
            return False
        if maps[x1][y] == 'X':
            break
    # y--
    for y1 in xrange(y - 1, -1, -1):
        if maps[x][y1] == 'M':
            return False
        if maps[x][y1] == 'X':
            break
    # y++
    for y1 in xrange(y + 1, count):
        if maps[x][y1] == 'M':
            return False
        if maps[x][y1] == 'X':
            break
    return True


def place(maps, i, count, place_count):
    if i == count ** 2:
        """
        maps = [''.join(row) for row in maps]
        print '\n'.join(maps)
        print '** ' * 10
        """
        global max_count
        if place_count > max_count:
            max_count = place_count
        return

    x, y = i / count, i % count
    can_place = can_place_if(maps, x, y, count)

    # place
    if can_place:
        current = maps[x][y]
        maps[x][y] = 'M'
        place(maps, i + 1, count, place_count + 1)
        maps[x][y] = current
    # not place
    place(maps, i + 1, count, place_count)


while 1:
    line = sys.stdin.readline()
    count = int(line.strip())
    if count == 0:
        break

    maps = []
    for i in xrange(count):
        line = sys.stdin.readline()
        line = line.strip()
        maps.append([char for char in line])

    # process
    max_count = 0
    place_count = 0
    place(maps, 0, count, place_count)
    print max_count
