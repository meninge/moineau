/*
 * src/helpers.h
 *
 * Helpers defines and weights definitions from generated Python file.
 */

#define DATA_BEGIN 0x10
#define LABEL_BEGIN 0x8
#define IMAGE_NUMBER 1000
//#define IMAGE_NUMBER 1
#define ROWS 28
#define COLUMNS 28

/*
 * Weights for the first layer.
 */
extern int16_t w1[NEURONS_FIRST_LAYER][28][28];
/*
 * Weights for the second layer.
 */
extern int16_t w2[10][NEURONS_FIRST_LAYER];
/*
 * Constants to add after computation at each layer.
 */
extern int16_t b1[NEURONS_FIRST_LAYER];
extern int16_t b2[10];

int32_t check_neurons_number();
uint8_t get_pixel(FILE *mnist_data, uint32_t image_number, uint32_t line,
		uint32_t column);
int16_t cut(int64_t in);
int32_t get_label(FILE *mnist_label, uint32_t image_number);
