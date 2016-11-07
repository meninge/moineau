/*
 * moineau/src/main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DATA_BEGIN 0xC

extern int16_t w1[NEURONS_FIRST_LAYER][28][28];
extern int16_t w2[10][NEURONS_FIRST_LAYER];
extern int16_t b1[NEURONS_FIRST_LAYER];
extern int16_t b2[10];

void check_neurons_number();

int main(int argc, char *argv[])
{
	check_neurons_number();

	return 0;
}

void check_neurons_number()
{
	FILE *net;
	char *first_line = NULL;
	int neurons;
	size_t n = 0;

#if NEURONS_FIRST_LAYER != 100 && NEURONS_FIRST_LAYER != 200
	printf("error: flag NEURONS_FIRST_LAYER must be 100 or 200\n");
	exit(1);
#endif
	net = fopen("src/net.c", "r");
	if (net == NULL) {
		printf("error: `src/net.c` file does not exist\n");
		exit(-1);
	}
	if (getline(&first_line, &n, net) < 0) {
		printf("error: can't read line\n");
		exit(-1);
	}
	sscanf(first_line, "//%d\n", &neurons);
	if (neurons != NEURONS_FIRST_LAYER) {
		printf("error: `src/net.c` must contain NEURONS_FIRST_LAYER neuron definitions\n");
		exit(-1);
	}
	free(first_line);
	fclose(net);
}
