# -*- coding: utf-8 -*-


def fake_data1():
    with open("../data/fake_data1_origin.csv", "w") as f:
        for i in xrange(100000000):
            f.write("%s\t%s\n" % (i, i))

    with open("../data/fake_data1_update.csv", "w") as f:
        for i in xrange(100000000):
            f.write("%s\t%s\n" % (i, i))

if __name__ == '__main__':
    fake_data1()
