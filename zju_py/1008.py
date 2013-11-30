# -*- coding: utf-8 -*-

import sys


def can_move(height, width, num, beyond_num, action, next_square):
    global now_queue, cannot
    if now_queue == []:
        return 1
    last_square = mm[now_queue[-1]]
    if last_square[action] != mm[next_square][(action + 2) % 4]:
        cannot[action][now_queue[-1]].add(next_square)
        cannot[(action + 2) % 4][next_square].add(now_queue[-1])
        return -1
    if beyond_num > 1:
        c_square_idx = num - 1
        if action in [0, 2]:
            c_square_idx -= ((width - 1) * 2 + height * 2 - 3)
        else:
            c_square_idx -= ((height - 1) * 2 + width * 2 - 3)
        if c_square_idx >= 0 and c_square_idx < num and \
                mm[next_square][(action + 1) % 4] != mm[now_queue[c_square_idx]][(action - 1) % 4]:
            cannot[(action - 1) % 4][now_queue[c_square_idx]].add(next_square)
            cannot[(action + 1) % 4][next_square].add(now_queue[c_square_idx])
            return -2

    return 1


def move(height, width, num, beyond_num, action):
    """
    height, width 当前阶段目标
    num 此次执行处理第几个
    beyond_num 包含此次执行落单不足以成一行的数量
    action 此次执行的方向0, 1, 2, 3
    """
    global used, now_queue, cannot, count
    if num == count ** 2:
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
    iter_set = set([k for k, v in used.iteritems() if v > 0])
    if now_queue != []:
        iter_set -= cannot[action][now_queue[-1]]
    for i in iter_set:
        if_can_move = can_move(height, width, num, beyond_num, action, i)
        if if_can_move == 1:
            used[i] -= 1
            now_queue.append(i)
            if move(next_height, next_width, num + 1, next_beyond_num, next_action):
                return True
            used[i] += 1
            now_queue.pop(-1)


iter_count = 0
while 1:
    iter_count += 1
    line = sys.stdin.readline()
    count = int(line.strip())
    if count == 0:
        break
    mm = []
    used = {}
    pre_check_set = set()
    pre_check_len = 0
    for i in xrange(count ** 2):
        line = sys.stdin.readline()
        line = line.strip()
        line = [int(num) for num in line.split()]
        for num in line:
            if num in pre_check_set:
                pre_check_set.discard(num)
                pre_check_len += 1
            else:
                pre_check_set.add(num)
        flag = True
        for j in xrange(len(mm)):
            if line == mm[j]:
                used[j] += 1
                flag = False
                break
        if flag:
            used[len(mm)] = 1
            mm.append(line)

    if pre_check_len < count * (count - 1) * 2:
        if_success = False
    else:
        # 二维数组 action, last
        cannot = [[set() for j in xrange(len(mm))] for i in xrange(4)]
        now_queue = []
        if_success = move(0, 0, 0, 0, 0)
    if iter_count > 1:
        print
    print 'Game %s: %s' % (iter_count, "Possible" if if_success else "Impossible")
