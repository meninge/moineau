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
	int64_t out1[NEURONS_FIRST_LAYER] = {0};
	int64_t out2[10] = {0};
	int32_t i, j, n, image;
	int32_t max = 0;
	int32_t success = 0;

	/*
	 * Check that Python parser generated file and make flags to generate
	 * the executable are for the same number of neurons.
	 */
	if (check_neurons_number() < 0) {
		printf("error: wrong neurons number\n");
		return -1;
	}
	for (image = 0; image < IMAGE_NUMBER; image++) {
		/*
		 * Initialization
		 */
		for (n = 0; n < NEURONS_FIRST_LAYER; n++) {
			out1[n] = 0;
		}
		for (n = 0; n < 10; n++) {
			out2[n] = 0;
		}
		max = 0;
		/*
		 * First layer computation
		 */
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLUMNS; j++) {
				for (n = 0; n < NEURONS_FIRST_LAYER; n++) {
					out1[n] += frames[image][i * ROWS + j]
						* w1[n][i * ROWS + j];
				}
			}
		}
		/*
		 * We need to cut values to 32 bits in between every layer.
		 */
		for (n = 0; n < NEURONS_FIRST_LAYER; n++) {
			out1[n] = cut(out1[n]);
			out1[n] += b1[n];
			out1[n] = (out1[n] > 0) ? out1[n] : 0;
			out1[n] = cut(out1[n]);
		}

		/*
		 * Second layer computation
		 */
		for (i = 0; i < NEURONS_FIRST_LAYER; i++) {
			for (n = 0; n < 10; n++) {
				out2[n] += out1[i] * w2[n][i];
			}
		}
		/*
		 * Apply second layer constants.
		 */
		for (n = 0; n < 10; n++) {
			out2[n] = cut(out2[n]);;
			out2[n] += b2[n];
			out2[n] = (out2[n] > 0) ? out2[n] : 0;
			out2[n] = cut(out2[n]);;
		}
		/*
		 * Compute the maximum value for the second layer
		 */
		for (i = 0; i < 10; i++) {
			if (out2[i] > out2[max])
				max = i;
		}
		/*
		 * Compute success rate
		 */
		if (max == labels[image]) {
			success++;
		}
	}
	printf("success rate: %.2f%%\n", (success / (float)IMAGE_NUMBER) * 100);

	return 0;
}
