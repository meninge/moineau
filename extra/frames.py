"""
file: moineau/extra/frames.py
author: Hugues de Valon

Parse MNIST datasets to create C arrays containing the frames and the labels.
"""

import sys

DATA_BEGIN = 0x10
LABEL_BEGIN = 0x8
IMAGE_NUMBER = 1000
ROWS = 28
COLUMNS = 28

def write_arrays(frame_number):
    if frame_number > IMAGE_NUMBER:
        raise Exception('Too much frames wanted')

    with open("../src/frames.c", "w+") as frames:
        frames.write("//%d\n" % frame_number)
        frames.write("#include <stdint.h>\n")
        # frames array
        frames.write("uint8_t frames[%d][%d] = {\n\t" % (frame_number, ROWS * COLUMNS))
        with open("../dataset/t10k-images-idx3-ubyte", "rb") as data:
            data.seek(DATA_BEGIN)
            for i in range(frame_number * ROWS * COLUMNS - 1):
                frames.write("%s, " % hex(ord(data.read(1))))
            frames.write("%s" % hex(ord(data.read(1))))
            print(data.read(1))
        frames.write("\n};\n")

        # labels array
        frames.write("uint8_t labels[%d] = {\n\t" % frame_number)
        with open("../dataset/t10k-labels-idx1-ubyte", "rb") as labels:
            labels.seek(LABEL_BEGIN)
            for i in range(frame_number - 1):
                frames.write("%s, " % hex(ord(labels.read(1))))
            frames.write("%s" % hex(ord(labels.read(1))))
        frames.write("\n};\n")

if len(sys.argv) == 2:
    write_arrays(int(sys.argv[1]))
else:
    write_arrays(1000)
