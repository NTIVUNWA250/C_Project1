/* Water Quality Analysis */
#include <stdio.h>

/*Ideal temperature of the water in Celsius*/
#define IDEAL_TEMPERATURE 25.0

/* Returns the difference between the temperature and the ideal temperature */
double temperature_deviation(double temperature)
{
    double difference = temperature - IDEAL_TEMPERATURE;
    if (difference < 0) {
        difference = -difference;
    }
    return difference;
}

/* This is to apply the index formula in the brief*/
double calculate_index(double temperature, double turbidity)
{
    double deviation = temperature_deviation(temperature);
    double turbidity_penalty = turbidity / 2.0;
    return 100.0 - (deviation + turbidity_penalty);
}

/* Returns the status of the index */
const char *classify_water(double index)
{
    if (index >= 80.0) {
        return "Good";
    }
    if (index >= 60.0) {
        return "Warning";
    }
    return "Critical";
}

int main(void)
{
    double temperature = 0.0;
    double turbidity = 0.0;
    double index = 0.0;

    printf("Enter water temperature in C: ");
    if (scanf("%lf", &temperature) != 1) {
        printf("Invalid temperature. Please enter a number.\n");
        return 1;
    }

    printf("Enter turbidity in NTU: ");
    if (scanf("%lf", &turbidity) != 1 || turbidity < 0) {
        printf("Invalid turbidity. Please enter a number of zero or more.\n");
        return 1;
    }

    index = calculate_index(temperature, turbidity);

    printf("\n===== WATER QUALITY MONITORING REPORT =====\n");
    printf("Temperature   : %.1f C\n", temperature);
    printf("Turbidity     : %.1f NTU\n", turbidity);
    printf("Quality index : %.1f\n", index);
    printf("Status        : %s\n", classify_water(index));

    return 0;
}
