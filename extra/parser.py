"""
file: moineau/extra/parser.py
author: Hugues de Valon

Parse weights file to produce C arrays:
    - net100.c
    - net200.c
Each one will contain weights and constants for each layer.
"""

import sys

def write_arrays(neurons_number):
    if neurons_number not in (100, 200):
        print("neurons number can only be 100 or 200.")
        return

    with open("../src/net.c", "w+") as net:
        net.write("//%d\n" % neurons_number)
        net.write("#include <stdint.h>\n")
        # w1 array
        net.write("int16_t w1[%d][28][28] = {\n\t" % neurons_number)
        with open("../weights/net%d/w1.txt" % neurons_number, "r") as w1:
            net.write(",".join([x.strip() for x in w1.readlines()]))
        net.write("\n};\n")

        # w2 array
        net.write("int16_t w2[10][%d] = {\n\t" % neurons_number)
        with open("../weights/net%d/w2.txt" % neurons_number, "r") as w2:
            net.write(",".join([x.strip() for x in w2.readlines()]))
        net.write("\n};\n")

        # b1 array
        net.write("int16_t b1[%d] = {\n\t" % neurons_number)
        with open("../weights/net%d/b1.txt" % neurons_number, "r") as b1:
            net.write(",".join([x.strip() for x in b1.readlines()]))
        net.write("\n};\n")

        # b2 array
        net.write("int16_t b2[10] = {\n\t")
        with open("../weights/net%d/b2.txt" % neurons_number, "r") as b2:
            net.write(",".join([x.strip() for x in b2.readlines()]))
        net.write("\n};\n")

if len(sys.argv) == 2:
    write_arrays(int(sys.argv[1]))
else:
    write_arrays(100)
