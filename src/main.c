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
	int64_t out1[NEURONS_FIRST_LAYER] = {0};
	int16_t out1_16[NEURONS_FIRST_LAYER] = {0};
	int64_t out2[10] = {0};
	int16_t out2_16[10] = {0};
	int32_t i, j, n, image;
	int32_t max = 0;
	int32_t errors = 0;

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

	for (image = 0; image < IMAGE_NUMBER; image++) {
		/*
		 * Initialization
		 */
		for (n = 0; n < NEURONS_FIRST_LAYER; n++) {
			out1[n] = 0;
			out1_16[n] = 0;
		}
		for (n = 0; n < 10; n++) {
			out2[n] = 0;
			out2_16[n] = 0;
		}
		max = 0;
		/*
		 * First layer computation
		 */
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLUMNS; j++) {
				for (n = 0; n < NEURONS_FIRST_LAYER; n++) {
					out1[n] += get_pixel(mnist_data,
							image, i, j)
						* w1[n][i][j];
				}
			}
		}
		/*
		 * Cut to 16 bits values and apply activation function
		 */
		for (n = 0; n < NEURONS_FIRST_LAYER; n++) {
			out1_16[n] = cut(out1[n]);
			//printf("before = %d, after = %d\n", out1[n], out1_16[n]);
			out1_16[n] += b1[n];
		}

		/*
		 * Second layer computation
		 */
		for (i = 0; i < NEURONS_FIRST_LAYER; i++) {
			for (n = 0; n < 10; n++) {
				out2[n] += out1_16[i] * w2[n][i];
			}
		}
		/*
		 * Apply second layer constants.
		 */
		for (n = 0; n < 10; n++) {
			out2_16[n] = cut(out2[n]);;
			out2_16[n] += b2[n];
		}
		/*
		 * Compute the maximum value for the second layer
		 */
		for (i = 0; i < 10; i++) {
			if (out2_16[i] > out2_16[max])
				max = i;
		}
		/*
		 * Compute error rate
		 */
		if (max != get_label(mnist_label, image))
			errors++;
	}
	printf("error rate: %.2f%%\n", (errors / (float)IMAGE_NUMBER) * 100);

	fclose(mnist_label);
	fclose(mnist_data);

	return 0;
}
