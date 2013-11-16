# -*- coding: utf-8 -*-

import sys
import math


sushu = set([2, 3, 5, 7, 11,
             13, 17, 19, 23, 29,
             31, 37, 41, 43, 47,
             53, 59, 61, 67, 71,
             73, 79, 83, 89, 97])


def check(no, next_):
    global elements
    if next_ == no:
        if elements == [] or next_ < elements[-1]:
            elements.append(next_)
            print elements
            elements.pop(-1)
        # 素数
        if no > 4 and no not in sushu:
            check(no, min(no / 2, 100))
    elif no > math.factorial(next_):
        return
    elif no % next_ == 0:
        if elements == [] or next_ < elements[-1]:
            tmp_no = no / next_
            tmp_next = tmp_no if elements == [] else min(elements[-1] - 1, tmp_no, 100)
            if tmp_next > 1:
                elements.append(next_)
                check(tmp_no, tmp_next)
                elements.pop(-1)
        # 若当前next_为素数，且已经导致no / next_为素数，则next_不往下减一
        if next_ in sushu and (no / next_) in sushu:
            return
        elif next_ > 2:
            check(no, next_ - 1)
    elif next_ > 2 and no not in sushu:
        check(no, min(next_ - 1, no / 2, 100))

elements = []
check(610, min(610, 100))

"""
def process(line):
    high_score, low_score = (int(i) for i in line.split())
    if high_score < low_score:
        high_score, low_score = low_score, high_score
    if not check(low_score, min(low_score, 100)):
        print high_score
    else:
        global elements
        elements = []
        if not check(low_score * high_score, min(low_score * high_score, 100)):
            print low_score
        else:
            print high_score

while 1:
    line = sys.stdin.readline()
    elements = []
    process(line)
"""
