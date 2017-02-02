"""
file: moineau/extra/frames.py
author: Hugues de Valon

Parse MNIST datasets to create C arrays containing the frames and the labels.

usage (place yourself in the same folder than this file):
    python frames.py [FRAMES_NUMBER] [MNIST_FRAMES_DATA] [MNIST_LABELS_DATA]
If no arguments are given use default behaviour: standard MNIST data.
"""

import sys

DATA_BEGIN = 0x10
LABEL_BEGIN = 0x8
IMAGE_NUMBER = 1000
ROWS = 28
COLUMNS = 28
FRAME_SIZE = ROWS * COLUMNS

"""
Create a C file containing two arrays, one for the MNIST frames and one for
the labels, ie the corresponding digits of these frames.
By default, use default MNIST data but you can give it as argument any
MNIST-formated data for your own images.
"""

def write_frames_array(mnist_frames_file, frame_number):
    if frame_number > IMAGE_NUMBER:
        raise Exception('Too much frames wanted')

    with open("../src/frames.c", "w+") as frames:
        frames.write("//%d\n" % frame_number)
        frames.write("#include <stdint.h>\n")
        # frames array
        frames.write("uint8_t frames[%d][%d] = {\n" % (frame_number, FRAME_SIZE))
        with open(mnist_frames_file, "rb") as data:
            data.seek(DATA_BEGIN)
            for i in range(frame_number - 1):
                frames.write("{")
                for j in range(FRAME_SIZE - 1):
                    frames.write("%s, " % hex(ord(data.read(1))))
                frames.write("%s},\n" % hex(ord(data.read(1))))
            frames.write("{")
            for j in range(FRAME_SIZE - 1):
                frames.write("%s, " % hex(ord(data.read(1))))
            frames.write("%s}" % hex(ord(data.read(1))))
        frames.write("\n};\n")

def write_labels_array(mnist_labels_file, frame_number):
    if frame_number > IMAGE_NUMBER:
        raise Exception('Too much frames wanted')

    with open("../src/frames.c", "a") as frames:
        # labels array
        frames.write("uint8_t labels[%d] = {\n" % frame_number)
        with open(mnist_labels_file, "rb") as labels:
            labels.seek(LABEL_BEGIN)
            for i in range(frame_number - 1):
                frames.write("%s, " % hex(ord(labels.read(1))))
            frames.write("%s" % hex(ord(labels.read(1))))
        frames.write("\n};\n")

if len(sys.argv) == 3:
    write_frames_array(sys.argv[2], int(sys.argv[1]))
elif len(sys.argv) == 4:
    write_frames_array(sys.argv[2], int(sys.argv[1]))
    write_labels_array(sys.argv[3], int(sys.argv[1]))
elif len(sys.argv) == 2:
    write_frames_array("../dataset/t10k-images-idx3-ubyte", int(sys.argv[1]))
    write_labels_array("../dataset/t10k-labels-idx1-ubyte", int(sys.argv[1]))
else:
    write_frames_array("../dataset/t10k-images-idx3-ubyte", 1000)
    write_labels_array("../dataset/t10k-labels-idx1-ubyte", 1000)
