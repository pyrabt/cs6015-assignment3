#!/usr/bin/env python

import os
import random

# define the name of the directory to be created
import shutil
import string

path = os.getcwd() + "/fuzzer_files"


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
    side_len = random.randint(1, 100)
    sq_coords = str(side_len) + " 0 " + str(side_len) + " " + str(side_len) + " 0 " + str(side_len)
    return sq_coords


def generate_square_cases():
    square_filenames = []
    for x in range(0, 100):
        name_of_file = "testSquare_" + str(x) + ".txt"
        square_file = open("fuzzer_files/" + name_of_file, 'w')
        square_file.write(random_square())
        square_filenames.append(name_of_file)
    return square_filenames


# generate a randomly sized rectangle
def random_rectangle():
    side_len1 = 0
    side_len2 = 0
    while side_len1 is side_len2:
        side_len1 = random.randint(1, 100)
        side_len2 = random.randint(1, 100)
    sq_coords = str(side_len1) + " 0 " + str(side_len1) + " " + str(side_len2) + " 0 " + str(side_len2)
    return sq_coords


def generate_rectangle_cases():
    rect_filenames = []
    for x in range(0, 100):
        name_of_file = "testRect_" + str(x) + ".txt"
        square_file = open("fuzzer_files/" + name_of_file, 'w')
        square_file.write(random_rectangle())
        rect_filenames.append(name_of_file)
    return rect_filenames


def random_ascii_string():
    return "".join(random.choice(string.ascii_letters + string.digits) for _ in range(0, 20))


def generate_random_ascii_cases():
    rand_ascii_filenames = []
    for x in range(0, 300):
        name_of_file = "testRandAscii_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(random_ascii_string())
        rand_ascii_filenames.append(name_of_file)
    return rand_ascii_filenames


# remove temp directory
def clean():
    try:
        shutil.rmtree(path)
    except OSError:
        print ("Deletion of the directory %s failed" % path)
    else:
        print ("Successfully deleted the directory %s" % path)


start()

for test_file in generate_square_cases():
    os.system("./classifier < fuzzer_files/" + test_file)

for test_file in generate_rectangle_cases():
    os.system("./classifier < fuzzer_files/" + test_file)

for test_file in generate_random_ascii_cases():
    os.system("./classifier < fuzzer_files/" + test_file)
clean()
