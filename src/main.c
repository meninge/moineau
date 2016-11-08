/*
 * moineau/src/main.c
 *
 * Main file that executes the loops.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
	FILE *mnist_label, *mnist_data;

	/*
	 * Check that Python parser generated file and make flags to generate
	 * the executable are for the same number of neurons.
	 */
	if (check_neurons_number() < 0) {
		printf("error: wrong neurons number\n");
		return -1;
	}
	/*
	 * Open MNIST dataset and labels.
	 */
	mnist_label = fopen("dataset/t10k-labels-idx1-ubyte", "rb");
	if (mnist_label == NULL) {
		printf("error: `dataset/t10k-labels-idx1-ubyte` file does not exist\n");
		return -1;
	}
	mnist_data = fopen("dataset/t10k-images-idx3-ubyte", "rb");
	if (mnist_data == NULL) {
		printf("error: `dataset/t10k-images-idx3-ubyte` file does not exist\n");
		return -1;
	}

	fclose(mnist_label);
	fclose(mnist_data);

	return 0;
}
