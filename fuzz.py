#!/usr/bin/env python

import os
import random

# define the name of the directory to be created
import shutil
import string

path = os.getcwd() + "/fuzzer_files"
prof_path = path + "/cov_data/"


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
    for x in range(0, 5000):
        name_of_file = "testRandAscii_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(random_ascii_string())
        rand_ascii_filenames.append(name_of_file)
    return rand_ascii_filenames


def random_quads():
    points = [random.randint(0, 100)]
    for p in range(5):
        points.append(random.randint(0, 150))
        q_coords = ''
    for point in points:
        q_coords = q_coords + str(point) + " "
    return q_coords


def generate_random_quad_cases():
    rand_quad_filenames = []
    for x in range(0, 5000):
        name_of_file = "testRandQuad_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(random_quads())
        rand_quad_filenames.append(name_of_file)
    return rand_quad_filenames


def random_num_of_points():
    points_to_make = random.randint(0, 50)
    output_line = ""
    for p in range(points_to_make):
        output_line = output_line + str(random.randint(0, 100)) + " "
    return output_line


def generate_random_input_size():
    rand_input_size_filenames = []
    for x in range(0, 5000):
        name_of_file = "testRandInput_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(random_num_of_points())
        rand_input_size_filenames.append(name_of_file)
    return rand_input_size_filenames


def duplicate_points():
    x1 = random.randint(0, 100)
    y1 = random.randint(0, 100)
    x2 = random.randint(0, 100)
    y2 = random.randint(0, 100)
    output_line = str(x1) + " " + str(y1) + " " + str(x2) + " " + str(y2) + " " + str(x1) + " " + str(y1)
    return output_line


def generate_dup_point():
    dup_point_flnames = []
    for x in range(0, 50):
        name_of_file = "testDupPoint_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(duplicate_points())
        dup_point_flnames.append(name_of_file)
    return dup_point_flnames


def collinear_points():
    x1 = random.randint(0, 25)
    y1 = random.randint(0, 25)
    output_line = str(x1) + " " + str(y1) + " " + str(x1 * 2) + " " + str(y1 * 2) + " " + str(x1 * 3) + " " + str(
        y1 * 3)
    return output_line


def generate_collin_points():
    coll_point_flnames = []
    for x in range(0, 50):
        name_of_file = "testCollinPoint_" + str(x) + ".txt"
        random_file = open("fuzzer_files/" + name_of_file, 'w')
        random_file.write(collinear_points())
        coll_point_flnames.append(name_of_file)
    return coll_point_flnames


def test_known_case(shape_case_gen, answerfile, coverage_flog, oracle_values):
    for test_file in shape_case_gen():
        spl_file = test_file.split(".txt")
        os.system("cd fuzzer_files/cov_data && LLVM_PROFILE_FILE=" + spl_file[0]
                  + ".profraw " + "../../classifier < ../" + test_file + " > " + spl_file[0] + "_res" + spl_file[1])
        coverage_flog.append(test_file.split(".txt")[0] + ".profraw")

        if os.system("diff -a fuzzer_files/cov_data/" + spl_file[0] + "_res" + spl_file[
            1] + " " + answerfile + "_ans.txt") is 0:
            oracle_values.append(0)
        else:
            oracle_values.append(1)


def test_random_case(rdm_generator, coverage_flog, oracle_vals):
    for test_file in rdm_generator():
        spl_file = test_file.split(".txt")
        os.system("cd fuzzer_files/cov_data && LLVM_PROFILE_FILE=" + spl_file[0]
                  + ".profraw " + "../../classifier < ../" + test_file + " > " + spl_file[0] + "_key" + spl_file[1])
        coverage_flog.append(test_file.split(".txt")[0] + ".profraw")

        os.system("cd fuzzer_files/cov_data && LLVM_PROFILE_FILE=" + spl_file[0]
                  + ".profraw " + "../../classifier < ../" + test_file + " > " + spl_file[0] + "_res" + spl_file[1])
        coverage_flog.append(test_file.split(".txt")[0] + ".profraw")

        if os.system("diff -a fuzzer_files/cov_data/" + spl_file[0] + "_key" + spl_file[1] + " fuzzer_files/cov_data/" +
                     spl_file[0] + "_key" + spl_file[1]) is 0:
            oracle_vals.append(0)
        else:
            oracle_vals.append(1)


def differential_test(rdm_generator):
    count = 0
    for test_file in rdm_generator():
        spl_file = test_file.split(".txt")

        os.system("cd fuzzer_files/cov_data && ../../classifier < ../" + test_file + " > " + spl_file[0] + "_me" + spl_file[1])

        os.system("cd fuzzer_files/cov_data && ../../benifier < ../" + test_file + " > " + spl_file[0] + "_ben" + spl_file[1])

        if os.system("diff -a fuzzer_files/cov_data/" + spl_file[0] + "_me" + spl_file[1] + " fuzzer_files/cov_data/" +
                     spl_file[0] + "_ben" + spl_file[1]) is not 0:
            print spl_file[0] + "_ben" + spl_file[1]
            count = count + 1
    return count


def run_diff_testing():
    discrepencies = 0
    os.mkdir(prof_path)

    discrepencies = discrepencies + differential_test(generate_random_ascii_cases)
    discrepencies = discrepencies + differential_test(generate_random_quad_cases)
    discrepencies = discrepencies + differential_test(generate_random_input_size)

    print "Number of errors: " + str(discrepencies)


def run_cases():
    os.mkdir(prof_path)

    cov_filenames = []
    heuristic_oracle = []
    rdm_test_oracle = []

    # Testing inputs with a known/expected key
    print "Drawing and testing trapezoids..."
    test_known_case(generate_trapezoid_cases, "trap", cov_filenames, heuristic_oracle)
    print "Drawing and testing squares..."
    test_known_case(generate_square_cases, "sqr", cov_filenames, heuristic_oracle)
    print "Drawing and testing rectangles..."
    test_known_case(generate_rectangle_cases, "rect", cov_filenames, heuristic_oracle)
    print "Drawing and testing parallelograms..."
    test_known_case(generate_parallelogram_cases, "para", cov_filenames, heuristic_oracle)
    print "Testing inputs with duplicate points..."
    test_known_case(generate_dup_point, "dup", cov_filenames, heuristic_oracle)
    print "Testing inputs with collinear points..."
    test_known_case(generate_collin_points, "collin", cov_filenames, heuristic_oracle)

    # Testing random inputs with a derived key from the initial run
    print "Testing random inputs...(LOTS)"
    test_random_case(generate_random_ascii_cases, cov_filenames, rdm_test_oracle)
    test_random_case(generate_random_quad_cases, cov_filenames, rdm_test_oracle)
    test_random_case(generate_random_input_size, cov_filenames, rdm_test_oracle)

    if heuristic_oracle.__contains__(1):
        print "Heuristic Key Oracle FAILURE"
    else:
        print "Heuristic Key Oracle PASSED"

    if rdm_test_oracle.__contains__(1):
        print "Random Test Oracle FAILURE"
    else:
        print "Random Test Oracle PASSED"

    if rdm_test_oracle.__contains__(1) or heuristic_oracle.__contains__(1):
        print "ERROR"
    else:
        print """OK 
                /@
                \ \ 
              ___> \ 
             (__O)  \ 
            (____@)  \ 
            (____@)   \ 
             (__o)_    \ 
                   \    \ """

    return cov_filenames


def produce_coveragefile(cov_files):
    hella_merg = ""
    for prof_file in cov_files:
        hella_merg = hella_merg + "fuzzer_files/cov_data/" + prof_file + " "
    os.system("xcrun llvm-profdata merge -sparse " + hella_merg + "-o coverage.txt")


# remove temp directory
def clean():
    try:
        shutil.rmtree(path)
    except OSError:
        print ("Deletion of the directory %s failed" % path)
    else:
        print ("Successfully deleted the directory %s" % path)


start()
#produce_coveragefile(run_cases())
run_diff_testing()
