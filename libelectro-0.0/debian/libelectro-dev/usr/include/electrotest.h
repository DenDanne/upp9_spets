#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NBR_OF_E12_RESISTORS 12
#define MAX_NBR_OF_RESISTORS 3
#define STEP 10
#define TOLERANCE 0.010f
#define NR_OF_COMPONENTS 3

float calc_resistance(int count, char conn, float *array);

float calc_power_r(float volt, float resistance);

float calc_power_i(float volt, float current);

void zero_setting(int from_index, int array_length, float *array);

int count_digits(float number);

int e_resistance(float orig_resistance, float *res_array);

void zero_setting(int from_index, int array_length, float *array);

int count_digits(float number);
