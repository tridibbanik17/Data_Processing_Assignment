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
void output_Data(float **arrayData, int rows, int cols) {
    printf("%d %d\n", rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < cols; column++) {
            printf("%.3f ", arrayData[row][column]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rows, cols, new_rows;
    float **arrayData = read_Data(&rows, &cols);

    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        float **cleaned_Data = clean_delete(arrayData, rows, cols, &new_rows);
        output_Data(cleaned_data, new_rows, cols);
        free(cleaned_data);
    } else {
        clean_impute(arrayData, rows, cols);
        output_data(arrayData, rows, cols);
    }

    for (int i = 0; i < rows; i++) {
        free(arrayData[i]);
    }
    free(arrayData);

    return 0;
}
