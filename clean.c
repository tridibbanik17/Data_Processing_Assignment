
/*Author: Tridib Banik, Student Number: 400514461, MacID: banikt       
 *This C program is a command line utility named clean that processes a two-dimensional grid of
  floating-point numbers for machine learning by replacing bad values with legal values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "read_data.h"
#include "clean.h"

// Replaces NAN values in each column with the column's average
void clean_impute(float **arrayData, int rows, int cols) {
    for (int column = 0; column < cols; column++) {
        float sum = 0.0;
        int count = 0;

        // Calculate column average
        for (int row = 0; row < rows; row++) {
            if (isnan(arrayData[row][column]) == 0) {
                sum += arrayData[row][column];
                count++;
            }
        }

        float average;
        if (count > 0) {
            average = sum / count;
        }
        else {
            average = 0.0;
        }

        // Replace NAN with average
        for (int row = 0; row < rows; row++) {
            if (isnan(arrayData[row][column]) != 0) {
                arrayData[row][column] = average;
            }
        }
    }
}

// Removes rows containing NAN values
float **clean_delete(float **arrayData, int rows, int cols, int *new_rows) {
    // Allocate memory for the filtered data array, initially the same size as the original array
    float **filtered_data = (float **)malloc(rows * sizeof(float *));
    // Initialize the count of new rows to 0
    *new_rows = 0;

    // Iterate over each row in the original array
    for (int row = 0; row < rows; row++) {
        // Initialize has_nan
        int has_nan = 0;

        // Iterate over each column in the current row
        for (int column = 0; column < cols; column++) {
            // Check if the current element is NAN
            if (isnan(arrayData[row][column]) != 0) {
                // NAN is found, so has_nan = 1
                has_nan = 1;
                break;
            }
        }

        // If the current row does not contain any NAN values
        if (has_nan == 0) {
            filtered_data[*new_rows] = arrayData[row];
            (*new_rows)++;
        }
    }

    // Reallocate memory for the filtered data array to match the number of valid rows
    filtered_data = (float **)realloc(filtered_data, *new_rows * sizeof(float *));
    return filtered_data;
}

// Outputs cleaned arrayData
void output_data(float **arrayData, int rows, int cols) {
    // Output the number of rows and columns on a single line
    printf("%d %d\n", rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < cols; column++) {
            // Output each float rounded to 3 decimal places
            printf("%.3f ", arrayData[row][column]);
        }
        // After each row is printed, the next row starts from a new line
        printf("\n");
    }
}

// Output the usage string
// void usage() {
//     printf("Usage: clean [-d]\n");
// }

// main() function takes command line arguments as its parameters
// main() function calls read_data, clean_impute, clean_delete and output_data.
int main(int argc, char *argv[]) {
    int rows, cols, new_rows;
    // Call read_data
    float **arrayData = read_data(&rows, &cols);

    // Check if the program was called with the "-d" argument
    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        // Call clean_delete to remove rows containing one or more NAN values
        float **cleaned_data = clean_delete(arrayData, rows, cols, &new_rows);
        // Call output_data to output the cleaned data to standard output
        output_data(cleaned_data, new_rows, cols);
        // Free the memory allocated for the cleaned data
        free(cleaned_data);
    } else {
        // If no "-d" argument, call clean_impute which replaces NAN values with the column's average
        clean_impute(arrayData, rows, cols);
        output_data(arrayData, rows, cols);
    } 
    //else {
    //    usage();
    //}

    // Free the memory allocated for each row in the original data
    for (int row = 0; row < rows; row++) {
        free(arrayData[row]);
    }
    // Free the memory allocated for arrayData
    free(arrayData);

    return 0;
}
