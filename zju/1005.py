import sys

def print_rs():
    global actions
    for action in actions:
        if action == 1:
            print "fill A"
        elif action == 2:
            print "empty A"
        elif action == 3:
            print "fill B"
        elif action == 4:
            print "empty B"
        elif action == 5:
            print "pour B A"
        elif action == 6:
            print "pour A B"
    print "success"


def fill(na, nb):
    global ca, cb, goal, hs
    if na == goal or nb == goal:
        print_rs()
        return True
    if (na, nb) in hs:
        return False
    hs.add((na, nb))
    if na < ca:
        actions.append(1)
        if fill(ca, nb):
            return True
        actions.pop(-1)
        if nb > 0:
            tmp = min(nb, ca - na)
            actions.append(5)
            if fill(na + tmp, nb - tmp):
                return True
            actions.pop(-1)
    actions.append(2)
    if fill(0, nb):
        return True
    actions.pop(-1)
    if nb < cb:
        actions.append(3)
        if fill(na, cb):
            return True
        actions.pop(-1)
        if na > 0:
            tmp = min(na, cb - nb)
            actions.append(6)
            if fill(na - tmp, nb + tmp):
                return True
            actions.pop(-1)

    actions.append(4)
    if fill(na, 0):
        return True
    actions.pop(-1)


while 1:
    line = sys.stdin.readline()
    if line.strip() == '':
        break
    ca, cb, goal = [int(i) for i in line.split()]
    hs = set()
    actions = []
    fill(0, 0)
