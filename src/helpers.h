/*
 * src/helpers.h
 *
 * Helpers defines and weights definitions from generated Python file.
 */

#define DATA_BEGIN 0x10
#define LABEL_BEGIN 0x8
#define IMAGE_NUMBER 1000
#define ROWS 28
#define COLUMNS 28
#define FRAME_SIZE ((ROWS) * (COLUMNS))

/*
 * Weights for the first layer.
 */
extern int16_t w1[NEURONS_FIRST_LAYER][FRAME_SIZE];
/*
 * Weights for the second layer.
 */
extern int16_t w2[10][NEURONS_FIRST_LAYER];
/*
 * Constants to add after computation at each layer.
 */
extern int16_t b1[NEURONS_FIRST_LAYER];
extern int16_t b2[10];

/*
 * Frames and labels
 */
extern uint8_t frames[IMAGE_NUMBER][FRAME_SIZE];
extern uint8_t labels[IMAGE_NUMBER];


int32_t check_neurons_number();
int64_t cut(int64_t in);
