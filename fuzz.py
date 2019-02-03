#!/usr/bin/env python

import os
import random

# define the name of the directory to be created
path = "/tmp/testFiles"


# create directory to do testing in
def start():
    try:
        os.mkdir(path)
    except OSError:
        print ("Creation of the directory %s failed" % path)
    else:
        print ("Successfully created the directory %s" % path)


# generate a randomly sized square
def random_square():
    side_len = random.randint(0, 101)
    sq_coords = str(side_len) + " 0 " + str(side_len) + " " + str(side_len) + " 0 " + str(side_len)
    return sq_coords


# generate a randomly sized rectangle
def random_rectangle():
    side_len1 = 0
    side_len2 = 0
    while side_len1 is side_len2:
        side_len1 = random.randint(0, 101)
        side_len2 = random.randint(0, 101)
    sq_coords = str(side_len1) + " 0 " + str(side_len1) + " " + str(side_len2) + " 0 " + str(side_len2)
    return sq_coords


# remove temp directory
def clean():
    try:
        os.rmdir(path)
    except OSError:
        print ("Deletion of the directory %s failed" % path)
    else:
        print ("Successfully deleted the directory %s" % path)


test_file = open("testSquare.txt", 'w')
test_file.write(random_square())
test_file.close()
test_file2 = open("testRect.txt", 'w')
test_file2.write(random_rectangle())
test_file2.close()
os.system("./classifier < testSquare.txt")
os.system("./classifier < testRect.txt")
