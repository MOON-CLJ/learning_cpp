# -*- coding: utf-8 -*-

import sys


def can_move(height, width, num, beyond_num, action, next_square):
    global now_queue
    if now_queue == []:
        return True
    last_square = mm[now_queue[-1]]
    if last_square[action] != next_square[(action + 2) % 4]:
        return False
    if beyond_num > 1:
        c_square_index = num - 1
        if action in [0, 2]:
            c_square_index -= ((width - 1) * 2 + height * 2 - 3)
        else:
            c_square_index -= ((height - 1) * 2 + width * 2 - 3)
        if c_square_index >= 0 and c_square_index < num and \
                next_square[(action + 1) % 4] != mm[now_queue[c_square_index]][(action - 1) % 4]:
            return False

    return True


def move(height, width, num, beyond_num, action):
    """
    height, width 当前阶段目标
    num 此次执行处理第几个
    beyond_num 包含此次执行落单不足以成一行的数量
    action 此次执行的方向0, 1, 2, 3
    """
    global unused, now_queue
    if num == len(mm):
        return True

    # 下个规模
    next_height, next_width = height, width
    if (action in [0, 2] and beyond_num == height) or (action in [1, 3] and beyond_num == width):
        next_beyond_num = 1
        if action in [0, 2]:
            next_height += 1
        else:
            next_width += 1
    else:
        next_beyond_num = beyond_num + 1
    next_action = action + 1 if beyond_num == 1 else action
    next_action %= 4
    for i in unused:
        if can_move(height, width, num, beyond_num, action, mm[i]):
            unused.discard(i)
            now_queue.append(i)
            if move(next_height, next_width, num + 1, next_beyond_num, next_action):
                return True
            unused.add(i)
            now_queue.pop(-1)


iter_count = 0
while 1:
    iter_count += 1
    line = sys.stdin.readline()
    count = int(line.strip())
    if count == 0:
        break
    mm = []
    for i in xrange(count ** 2):
        line = sys.stdin.readline()
        line = line.strip()
        mm.append([int(i) for i in line.split()])

    unused = set([i for i in xrange(len(mm))])
    now_queue = []
    if_success = move(0, 0, 0, 0, 0)
    if iter_count > 1:
        print
    print 'Game %s: %s' % (iter_count, "Possible" if if_success else "Impossible")
