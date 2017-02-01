"""
file: moineau/extra/parser.py
author: Hugues de Valon

Parse weights file to produce C arrays:
    - net100.c
    - net200.c
Each one will contain weights and constants for each layer.
"""

import sys

"""
Write four arrays:
	- w1: weights for the first level
	- w2: weights for the second level
	- b1: recode data for the first layer
	- b2: recode data for the second layer
"""
def write_arrays(neurons_number):
    if neurons_number not in (100, 200):
        print("neurons number can only be 100 or 200.")
        return

    with open("../src/net.c", "w+") as net:
        # The number of neurons is added as a C comment at the beginning of
	# the file to be used as a checker.
        net.write("//%d\n" % neurons_number)
        net.write("#include <stdint.h>\n")
        # w1 array
        net.write("int16_t w1[%d][784] = {\n" % neurons_number)
        with open("../weights/net%d/w1.txt" % neurons_number, "r") as w1:
            for x in w1.read().splitlines()[:-1]:
                net.write("{")
                net.write(x)
                net.write("},\n")
            w1.seek(0)
            net.write("{" + w1.read().splitlines()[-1] + "}")
        net.write("\n};\n")

        # w2 array
        net.write("int16_t w2[10][%d] = {\n" % neurons_number)
        with open("../weights/net%d/w2.txt" % neurons_number, "r") as w2:
            for x in w2.read().splitlines()[:-1]:
                net.write("{")
                net.write(x)
                net.write("},\n")
            w2.seek(0)
            net.write("{" + w2.read().splitlines()[-1] + "}")
        net.write("\n};\n")

        # b1 array
        net.write("int16_t b1[%d] = {\n" % neurons_number)
        with open("../weights/net%d/b1.txt" % neurons_number, "r") as b1:
            net.write(",".join([x.strip() for x in b1.readlines()]))
        net.write("\n};\n")

        # b2 array
        net.write("int16_t b2[10] = {\n")
        with open("../weights/net%d/b2.txt" % neurons_number, "r") as b2:
            net.write(",".join([x.strip() for x in b2.readlines()]))
        net.write("\n};\n")

if len(sys.argv) == 2:
    write_arrays(int(sys.argv[1]))
else:
    write_arrays(100)
