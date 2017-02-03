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
		printf("error: neuron number mismatch\n");
		printf("If you switched from 100 to 200 neurons, make sure that you used the following commands in that order to compile:\n");
		printf("make clean\n");
		printf("make parse NEURONS=200\n");
		printf("make NEURONS=200\n");
		return -1;
	}
	free(first_line);
	fclose(net);

	return 0;
}

/*
 * Keep only 32 bits from in, in a signed 64 bits word.
 */
int64_t cut(int64_t in)
{
	bool negative;

	negative = (in < 0) ? true : false;
	if (negative)
		in = -in;
	in &= 0x00000000FFFFFFFF;
	// NEURONS = 200
	//in &= 0x00000000FFFFFFFF; 94.4% (HARDWARE)
	//in &= 0x000000FFFFFFFF00; 8.5%
	//in &= 0x0000000FFFFFFFF0; 94.7%
	//in &= 0x0000003FFFFFFFC0; 89.4%
	//in &= 0x0000001FFFFFFFE0; 94.8%
	//in &= 0x00000007FFFFFFF8; 94.5%
	// NEURONS = 100
	//in &= 0x00000000FFFFFFFF; 93.8% (HARDWARE)
	//in &= 0x000000FFFFFFFF00; 8.5%
	//in &= 0x0000000FFFFFFFF0; 93.9%
	//in &= 0x0000003FFFFFFFC0; 79.4%
	//in &= 0x0000001FFFFFFFE0; 94.3%
	//in &= 0x00000007FFFFFFF8; 93.9%
	//in >>= 3;
	if (negative)
		in = -in;

	return in;
}
