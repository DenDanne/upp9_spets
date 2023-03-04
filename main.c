#include "electrotest.h"

int main(void){
	int voltage;
	char koppling[2];
	int nr_comp;

	printf("Ange spänningskälla i V: ");
	scanf("%d", &voltage);

	printf("Ange koppling[S | P]: ");
	scanf("%1s", (char*)koppling);

	printf("Antal komponenter: ");
	scanf("%d", &nr_comp);

        float* resistance_array;
        resistance_array =  malloc(nr_comp * sizeof(float));


	for(int i = 1 ; i <= nr_comp ; i++){
		printf("Komponent %d i ohm: ", i);
		scanf("%f", &resistance_array[i-1]);
	}

	float ersattning = calc_resistance(nr_comp, koppling[0], resistance_array);

	printf("Ersättningsreistans:\n%.1f ohm", ersattning);

	printf("\nEffekt:\n%.2f W", calc_power_r(voltage, ersattning));

	float* res_array;
	res_array = malloc(NR_OF_COMPONENTS * sizeof(float));
	int count =  e_resistance(ersattning, res_array);

	printf("\nErsättningsresistanser i E12-serien kopplade i serie:\n");

	for(int i = 0 ; i < count ; i++){
		printf("%.0f\n", res_array[i]);
	}

	free(resistance_array);
	free(res_array);

	return 0;
}
