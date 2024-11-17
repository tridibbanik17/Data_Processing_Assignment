/* Author: Tridib Banik, Student Number: 400514461, MacID: banikt       
 * This C program is a command line utility named clean that processes a two-dimensional grid of
 * floating-point numbers for machine learning by replacing bad values with legal values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "read_data.h"
#include "clean.h"

// Replaces NAN values in each column with the column's average
void clean_impute(float **arrayData, int rows, int cols) {
    for (int column = 0; column < cols; column++) {
        float sum = 0.0;
        int count = 0;

        // Calculate column average
        for (int row = 0; row < rows; row++) {
            if (!isnan(arrayData[row][column])) {
                sum += arrayData[row][column];
                count++;
            }
        }

        // Compute the average or use the default value
        float average = (count > 0) ? (sum / count) : DEFAULT_VALUE;

        // Replace NAN values with the average
        for (int row = 0; row < rows; row++) {
            if (isnan(arrayData[row][column])) {
                arrayData[row][column] = average;
            }
        }
    }
}

// Removes rows containing NAN values
float **clean_delete(float **arrayData, int rows, int cols, int *new_rows) {
    // Allocate memory for the filtered data array
    float **filtered_data = (float **)malloc(rows * sizeof(float *));
    *new_rows = 0;

    // Iterate over each row
    for (int row = 0; row < rows; row++) {
        int has_nan = 0;

        // Check if the current row contains a NAN value
        for (int column = 0; column < cols; column++) {
            if (isnan(arrayData[row][column])) {
                has_nan = 1;
                break;
            }
        }

        // If no NAN values, keep the row
        if (!has_nan) {
            filtered_data[*new_rows] = arrayData[row];
            (*new_rows)++;
        }
    }

    // Reallocate memory to match the number of valid rows
    filtered_data = (float **)realloc(filtered_data, (*new_rows) * sizeof(float *));
    return filtered_data;
}

// Outputs the cleaned data
void output_data(float **arrayData, int rows, int cols) {
    printf("%d %d\n", rows, cols);  // Output the number of rows and columns
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < cols; column++) {
            printf(OUTPUT_PRECISION " ", arrayData[row][column]);  // Output values with precision
        }
        printf("\n");  // New line for each row
    }
}

// Main function
int main(int argc, char *argv[]) {
    int rows, cols, new_rows;

    // Read data from standard input
    float **arrayData = read_data(&rows, &cols);

    if (!arrayData) {
        fprintf(stderr, "Error: Unable to allocate memory for input data.\n");
        return EXIT_FAILURE;
    }

    // Check if the program was called with the "-d" argument
    if (argc == 2 && strcmp(argv[1], DELETE_MODE) == 0) {
        // Call clean_delete to remove rows containing one or more NAN values
        float **cleaned_data = clean_delete(arrayData, rows, cols, &new_rows);
        if (cleaned_data) {
            output_data(cleaned_data, new_rows, cols);  // Output the cleaned data
            free(cleaned_data);  // Free memory for cleaned data
        }
    } else if (argc == 1) {
        // Call clean_impute to replace NAN values with column averages
        clean_impute(arrayData, rows, cols);
        output_data(arrayData, rows, cols);  // Output the cleaned data
    } else {
        // If invalid arguments, print usage message
        printf(USAGE_MESSAGE);
    }

    // Free memory for the original data
    for (int row = 0; row < rows; row++) {
        free(arrayData[row]);
    }
    free(arrayData);

    return EXIT_SUCCESS;
}

