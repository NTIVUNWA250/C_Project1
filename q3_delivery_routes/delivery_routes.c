/* Delivery Routes Analysis */

#include <stdio.h>

#define MAX_ROUTES 100

/* Adds up edistances using a plain loop */
int total_distance(const int distances[], int count)
{
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += distances[i];
    }
    return total;
}

/* Calculates average distance by reusing the total_distance */
double average_distance(const int distances[], int count)
{
    if (count == 0) {
        return 0.0;
    }
    return (double) total_distance(distances, count) / count;
}

/* Keeps the longest distance/route tracked */
int longest_route(const int distances[], int count)
{
    int longest = distances[0];
    for (int i = 1; i < count; i++) {
        if (distances[i] > longest) {
            longest = distances[i];
        }
    }
    return longest;
}

/* Counts the routes strictly longer than the limit */
int count_above_limit(const int distances[], int count, int limit)
{
    int above = 0;
    for (int i = 0; i < count; i++) {
        if (distances[i] > limit) {
            above++;
        }
    }
    return above;
}

/*
 * This is for counting the total distance recursively.
 */
int recursive_sum(const int distances[], int count)
{
    if (count == 0) {
        return 0;
    }
    return distances[count - 1] + recursive_sum(distances, count - 1);
}

/*Main function to call all the other functions, allow user input, and print the results to the user*/
int main(void)
{
    int distances[MAX_ROUTES];
    int count = 0;
    int limit = 0;
    double average = 0.0;

    printf("Number of routes: ");
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_ROUTES) {
        printf("Please enter a number of routes between 1 and %d.\n", MAX_ROUTES);
        return 1;
    }

    printf("Distances: ");
    for (int i = 0; i < count; i++) {
        if (scanf("%d", &distances[i]) != 1 || distances[i] < 0) {
            printf("Distances must be whole numbers of zero or more.\n");
            return 1;
        }
    }

    printf("Distance limit: ");
    if (scanf("%d", &limit) != 1) {
        printf("Please enter a whole number for the limit.\n");
        return 1;
    }

    average = average_distance(distances, count);

    printf("\n===== DELIVERY DISTANCE ANALYSIS =====\n\n");
    printf("Total distance: %d km\n", total_distance(distances, count));
    printf("Average distance: %.2f km\n", average);
    printf("Longest route: %d km\n", longest_route(distances, count));
    printf("Routes above %d km: %d\n", limit, count_above_limit(distances, count, limit));
    /* now, the limit is the average but the function is still the same */
    printf("Routes above average: %d\n", count_above_limit(distances, count, (int) average));
    printf("\nRecursive sum: %d km\n", recursive_sum(distances, count));

    return 0;
}