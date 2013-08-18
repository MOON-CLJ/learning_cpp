# -*- coding: utf-8 -*-


def fake_data1():
    with open("../data/fake_data1_origin.csv", "w") as f:
        for i in xrange(100000000):
            f.write("%s\t%s\n" % (i, i))

    with open("../data/fake_data1_update.csv", "w") as f:
        for i in xrange(100000000):
            f.write("%s\t%s\n" % (i, i))


def fake_data2():
    with open("../data/fake_data2_origin.csv", "w") as f:
        for i in xrange(1000000):
            if i % 2 == 0:
                f.write("%s\t%s\n" % (i, i))

    with open("../data/fake_data2_update.csv", "w") as f:
        for i in xrange(1000000):
            if i % 2 == 1:
                f.write("%s\t%s\n" % (i, i))


def fake_data3():
    with open("../data/fake_data3_origin.csv", "w") as f:
        for i in xrange(50000, 500000):
            f.write("%s\t%s\n" % (i, i))

    with open("../data/fake_data3_update.csv", "w") as f:
        for i in xrange(0, 550000):
            f.write("%s\t%s\n" % (i, i))


if __name__ == '__main__':
    # fake_data1()
    # fake_data2()
    fake_data3()
