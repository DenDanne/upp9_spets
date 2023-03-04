#include "electrotest.h"

float calc_resistance(int count, char conn, float *array){
	if(array[0] == 0){
		return -1;
	}

	float total_resistance = 0;

	if(conn == 'S'){
		for(int i = 0 ; i < count ; i++){
			total_resistance += array[i];
		}
		return total_resistance;
	}
	else if(conn == 'P'){
		float inverse_resistance = 0;
		for(int i = 0 ; i < count ; i++){
			inverse_resistance += (1 / array[i]);
		}
		total_resistance = 1 / inverse_resistance;
		return total_resistance;
	}
	else{
		return -1;
	}

	return 0;
}

float calc_power_r(float volt, float resistance)
{
    return powf(volt, 2.0) / resistance;
}

float calc_power_i(float volt, float current)
{
    return volt * current;
}


void zero_setting(int from_index, int array_length, float *array);
int count_digits(float number);

//https://sv.wikipedia.org/wiki/E-serie_(elektronik)
static const float E12_RESISTORS[] = {
    1.0f,
    1.2f,
    1.5f,
    1.8f,
    2.2f,
    2.7f,
    3.3f,
    3.9f,
    4.7f,
    5.6f,
    6.8f,
    8.2f
  };

/* Beräknar vilka tre seriekopllade resistorer i E12-serien som
 * närmast ersätter den resistance som skickas med.
 *
 * @param   orig_resistance   Ersättningsresistansen
 *          *res_array        Pekare till en array innehållande 3 resistorer
 *                            med värden ur E12-serien.
 * @return  nbr_of_resistors  Int [0-3].
 *                            Antal resistorer som behövs för att ersätta
 *                            orig_resistance.
 */
int e_resistance(float orig_resistance, float *res_array) {

  if (orig_resistance <= 0) {
    zero_setting(0, MAX_NBR_OF_RESISTORS, res_array);
    return 0;
  }

  int nbr_of_resistors  = 0;
  float rest_resistance = orig_resistance;
  int nbr_of_digits     = count_digits(orig_resistance);
  int E12_index         = NBR_OF_E12_RESISTORS - 1;

  while (fabsf(rest_resistance) > orig_resistance * TOLERANCE
         &&  nbr_of_resistors < MAX_NBR_OF_RESISTORS) {

    if (E12_index < 0) {
      E12_index        = NBR_OF_E12_RESISTORS - 1;
      nbr_of_digits   -= 1;
    }

    float resistor_value = E12_RESISTORS[E12_index]
                           * powf(10, (nbr_of_digits - 1));

    if (rest_resistance >= resistor_value) {
      res_array[nbr_of_resistors] = resistor_value;
      nbr_of_resistors           += 1;
      rest_resistance            -= resistor_value;
    }

    /* printf("DEBUGG: power           = %f\n", powf(10, (nbr_of_digits - 1))); */
    /* printf("DEBUGG: E12 Index       = %d\n", E12_index); */
    /* printf("DEBUGG: resistor value  = %f\n", resistor_value); */
    /* printf("DEBUGG: rest_resistance = %f\n", rest_resistance); */

    E12_index -= 1;
  }

  // Om inte alla komponenter används, nollställ dem.
  zero_setting(nbr_of_resistors, MAX_NBR_OF_RESISTORS, res_array);

  return nbr_of_resistors;
}

void zero_setting(int from_index, int array_length, float *array) {
  for (int i = from_index; i < array_length; i++) {
    array[i] = 0;
  }
}

int count_digits(float number) {
  int count = 0;
  count = (number == 0)? 1 : log10f(number) + 1;
  /* printf("DEBUGG: cout_digits: %d \n", count); */
  return count;
}

