#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "read_data.h"

// Reads and returns a rectangular array of floats filled with values from standard input
float **read_data(int *rows, int *cols) {
    // Read the number of rows and columns as two integers from standard input.
    scanf("%d %d", rows, cols);

    // Allocate memory for rows
    float **arrayData = (float **)malloc(*rows * sizeof(float *));
    for (int item = 0; item < *rows; item++) {
        arrayData[item] = (float *)malloc(*cols * sizeof(float));
    }

    // Read the grid data
    for (int row = 0; row < *rows; row++) {
        for (int column = 0; column < *cols; column++) {
            if (scanf("%f", &arrayData[row][column]) != 1) {
                // Invalid input will be replaced by NAN.
                arrayData[row][column] = NAN; 
            }
        }
    }

    return arrayData;

} 

