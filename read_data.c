#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_data.h"
#include "clean.h" 

// Reads and returns a rectangular array of floats filled with values from standard input
float **read_data(int *rows, int *cols) {
    // Read the number of rows and columns as two integers from standard input
    if (scanf("%d %d", rows, cols) != 2 || *rows <= 0 || *cols <= 0 || *rows > MAX_ROWS || *cols > MAX_COLS) {
        fprintf(stderr, "Error: Invalid input for rows and columns. Must be integers within range 1-%d for rows and 1-%d for columns.\n", MAX_ROWS, MAX_COLS);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for rows
    float **arrayData = (float **)malloc(*rows * sizeof(float *));
    if (arrayData == NULL) {
        fprintf(stderr, "Error: Memory allocation for rows failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int row = 0; row < *rows; row++) {
        arrayData[row] = (float *)malloc(*cols * sizeof(float));
        if (arrayData[row] == NULL) {
            fprintf(stderr, "Error: Memory allocation for columns in row %d failed.\n", row);
            // Free previously allocated memory for rows
            for (int i = 0; i < row; i++) {
                free(arrayData[i]);
            }
            free(arrayData);
            exit(EXIT_FAILURE);
        }
    }

    // Read the grid data
    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            if (scanf("%f", &arrayData[row][col]) != 1) {
                // Invalid input will be replaced by NAN
                arrayData[row][col] = NAN_VALUE; // Use the constant defined in clean.h
            }
        }
    }

    return arrayData;
}
