import sys


def move():
    global actions
    global tmp
    global now
    global target

    if len(actions) == len(target) * 2 and now == target:
        print ' '.join(actions), ''
    i = 0
    continue_flag = True
    while i < len(now):
        if target[i] != now[i]:
            continue_flag = False
            break
        i += 1
    if continue_flag:
        if len(origin) > 0:
            actions.append('i')
            tmp.insert(0, origin.pop(0))
            move()
            origin.insert(0, tmp.pop(0))
        if len(tmp) > 0:
            actions.append('o')
            now.append(tmp.pop(0))
            move()
            tmp.insert(0, now.pop(-1))
    if len(actions):
        actions.pop(-1)

while 1:
    origin_str = sys.stdin.readline()
    if origin_str.strip() == '':
        break
    target_str = sys.stdin.readline()
    origin = [i for i in origin_str.strip()]
    target = [i for i in target_str.strip()]
    actions = []
    tmp = []
    now = []
    print '['
    move()
    print ']'
