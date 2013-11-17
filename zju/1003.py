# -*- coding: utf-8 -*-

import sys


def check(low_score, high_score, now):
    if (low_score == 1 and high_score == 1) or \
            (low_score < now and high_score < now and low_score != high_score):
        global g_high_score
        print g_high_score
        return True
    if now == 1:
        if low_score == 1:
            global flag_low
            flag_low = True
        return False
    if low_score % now == 0:
        if check(low_score / now, high_score, now - 1):
            return True
    if high_score % now == 0:
        if check(low_score, high_score / now, now - 1):
            return True
    if check(low_score, high_score, now - 1):
        return True


while 1:
    line = sys.stdin.readline()
    if line.strip() == '':
        break
    elements = []
    g_high_score, g_low_score = (int(i) for i in line.split())
    if g_high_score < g_low_score:
        g_high_score, g_low_score = g_low_score, g_high_score
    flag_low = False
    if not check(g_low_score, g_high_score, min(100, max(g_low_score, g_high_score))):
        if flag_low:
            print g_low_score
        else:
            print g_high_score
