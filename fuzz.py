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


def random_parallelogram():
    side_len1 = 0
    side_len2 = 0

    while side_len1 is side_len2:
        side_len1 = random.randint(1, 90)
        side_len2 = random.randint(1, 100)

    shift = (100 - side_len1) / 2

    para_coords = str(side_len1) + " 0 " + str(side_len1 + shift) + " " + str(side_len2) + " " + str(shift) + " " + str(
        side_len2)
    return para_coords


def generate_parallelogram_cases():
    para_filenames = []
    for x in range(0, 100):
        name_of_file = "testPara_" + str(x) + ".txt"
        square_file = open("fuzzer_files/" + name_of_file, 'w')
        square_file.write(random_parallelogram())
        para_filenames.append(name_of_file)
    return para_filenames


def random_trapezoid():
    side_len1 = random.randint(5, 100)
    side_len2 = random.randint(1, 100)
    upper_bound = side_len1 / 4
    shift = random.randint(1, upper_bound)

    trp_coords = str(side_len1) + " 0 " + str(side_len1 - shift) + " " + str(side_len2) + " " + str(shift) + " " + str(
        side_len2)
    return trp_coords


def generate_trapezoid_cases():
    trap_filenames = []
    for x in range(0, 100):
        name_of_file = "testTrap_" + str(x) + ".txt"
        square_file = open("fuzzer_files/" + name_of_file, 'w')
        square_file.write(random_trapezoid())
        trap_filenames.append(name_of_file)
    return trap_filenames


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


def random_quads():
    points = [random.randint(0, 100)]
    for p in range(5):
        points.append(random.randint(0, 100))
        sq_coords = ''
    for point in points:
        sq_coords = sq_coords + str(point) + " "
    return sq_coords


def generate_random_quad_cases():
    rand_quad_filenames = []
    for x in range(0, 500):
        name_of_file = "testRandQuad_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(random_quads())
        rand_quad_filenames.append(name_of_file)
    return rand_quad_filenames


def generate_run_cases():
    cov_filenames =[]
    prof_path = path + "/cov_data/"
    os.mkdir(prof_path)

    for test_file in generate_trapezoid_cases():
        os.system("cd fuzzer_files/cov_data && LLVM_PROFILE_FILE=" + test_file.split(".txt")[0] + ".profraw " + "../../classifier < ../" + test_file)
        cov_filenames.append(test_file.split(".txt")[0] + ".profraw")

#    for test_file in generate_square_cases():
 #       os.system("LLVM_PROFILE_FILE=" + test_file + ".profraw " + "./classifier < fuzzer_files/" + test_file)

  #  for test_file in generate_rectangle_cases():
   #     os.system("LLVM_PROFILE_FILE=" + test_file + ".profraw " + "./classifier < fuzzer_files/" + test_file)

    #for test_file in generate_parallelogram_cases():
     #   os.system("LLVM_PROFILE_FILE=" + test_file + ".profraw " + "./classifier < fuzzer_files/" + test_file)

    #for test_file in generate_random_ascii_cases():
     #   os.system("LLVM_PROFILE_FILE=" + test_file + ".profraw " + "./classifier < fuzzer_files/" + test_file)

    #for test_file in generate_random_quad_cases():
     #   os.system("LLVM_PROFILE_FILE=" + test_file + ".profraw " + "./classifier < fuzzer_files/" + test_file)

    return cov_filenames

def produce_coveragefile(cov_files):
    print os.getcwd()
    hella_merg = ""
    for file in cov_files:
        hella_merg = hella_merg + "fuzzer_files/cov_data/" + file + " "
    print hella_merg + "-o rdmtesting.profdata"
    os.system("xcrun llvm-profdata merge -sparse " + hella_merg + "-o rdmTesting.profdata")


# remove temp directory
def clean():
    try:
        shutil.rmtree(path)
    except OSError:
        print ("Deletion of the directory %s failed" % path)
    else:
        print ("Successfully deleted the directory %s" % path)


start()
produce_coveragefile(generate_run_cases())
clean()