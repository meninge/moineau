/*
 * src/helpers.c
 * Helpers functions to compute the loops and access data from files.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "helpers.h"

/*
* Check that Python parser generated file and make flags to generate
* the executable are for the same number of neurons.
* Returns 0 if success or -1 for error.
*/
int32_t check_neurons_number()
{
	FILE *net;
	char *first_line = NULL;
	int neurons;
	size_t n = 0;

#if NEURONS_FIRST_LAYER != 100 && NEURONS_FIRST_LAYER != 200
	printf("error: flag NEURONS_FIRST_LAYER must be 100 or 200\n");
	return -1;
#endif
	/*
	 * The net.c file contains in comments the number of neurons.
	 * This value must be equal to NEURONS_FIRST_LAYER.
	 */
	net = fopen("src/net.c", "r");
	if (net == NULL) {
		printf("error: `src/net.c` file does not exist\n");
		return -1;
	}
	if (getline(&first_line, &n, net) < 0) {
		printf("error: can't read line\n");
		return -1;
	}
	sscanf(first_line, "//%d\n", &neurons);
	if (neurons != NEURONS_FIRST_LAYER) {
		printf("error: `src/net.c` must contain NEURONS_FIRST_LAYER neuron definitions\n");
		return -1;
	}
	free(first_line);
	fclose(net);

	return 0;
}

/*
 * Get one pixel value from the MNIST test set. The mnist_data file must be
 * opened before calling this function.
 * Return the pixel value if success and 0 if an error occured.
 */
uint8_t get_pixel(FILE *mnist_data, uint32_t image_number, uint32_t line,
		uint32_t column)
{
	uint8_t pixel;
	long image_offset;

	if (image_number >= 1000 || line >= ROWS || column >= COLUMNS) {
		printf("error: wrong get_pixel arguments\n");
		return 0;
	}

	image_offset = DATA_BEGIN + image_number * ROWS * COLUMNS;
	if (fseek(mnist_data, image_offset + line * COLUMNS + column, SEEK_SET)
			< 0) {
		printf("error: can't seek into file\n");
		return 0;
	}
	if (fread(&pixel, 1, 1, mnist_data) == 0) {
		printf("error: can't read pixel\n");
		return 0;
	}

	return pixel;
}

/*
 * Get the label for the corresponding image in the MNIST test set. The label
 * file must be opened before calling this function.
 * Returns the label value if success or -1 if an error occured.
 */
int32_t get_label(FILE *mnist_label, uint32_t image_number)
{
	uint8_t label;
	long label_offset;

	if (image_number >= 1000) {
		printf("error: wrong image_number argument\n");
		return -1;
	}
	label_offset = LABEL_BEGIN + image_number;
	if (fseek(mnist_label, label_offset, SEEK_SET) < 0) {
		printf("error: can't seek into file\n");
		return -1;
	}
	if (fread(&label, 1, 1, mnist_label) == 0) {
		printf("error: can't read pixel\n");
		return -1;
	}

	return (int32_t)label;
}

/*
 * Take the 16 highest bits from in.
 */
int16_t cut(int64_t in)
{
	bool negative;
	int16_t out;

	negative = (in < 0) ? true : false;
	if (negative)
		in = -in;
	//in &= 0xFFFF0000; 91.3% error
	//in &= 0x0FFFF000; 91.3% error
	//in &= 0x03FFFC00; 83.10% error
	//in &= 0x01FFFE00; 28.80% error
	//in &= 0x00FFFF00; 11.60% error
	//in &= 0x007FFF80; 16.30% error
	//in &= 0x000FFFF0; 90.70% error
	in &= 0x00FFFF00;
	in >>= 8;
	out = (int16_t)in;
	if (negative)
		out = -out;

	return out;
}
