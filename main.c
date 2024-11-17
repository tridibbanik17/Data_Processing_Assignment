
/*Author: Tridib Banik, Student Number: 400514461, MacID: banikt       
 *This C program calls read_data, clean_impute, clean_delete and output_data.
 */

#include<stdio.h>
#include<stdlib.h>
#include "clean.h"
#include "read_data.h"
#include "main.h"

void usage() {
    printf("Usage: clean [-d]\n");
}

// main() function takes command line arguments as its parameters
int main(int argc, char *argv[]) {
    int rows, cols, new_rows;
    // Call read_data
    float **arrayData = read_Data(&rows, &cols);

    // Check if the program was called with the "-d" argument
    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        // Call clean_delete to remove rows containing one or more NAN values
        float **cleaned_Data = clean_delete(arrayData, rows, cols, &new_rows);
        // Call output_data to output the cleaned data to standard output
        output_Data(cleaned_data, new_rows, cols);
        // Free the memory allocated for the cleaned data
        free(cleaned_data);
    } else if ((argc > 1) && (strcmp(argv[1], "-d") != 0)) {
        // If no "-d" argument, call clean_impute which replaces NAN values with the column's average
        clean_impute(arrayData, rows, cols);
        output_data(arrayData, rows, cols);
    } else {
        usage();
    }

    // Free the memory allocated for each row in the original data
    for (int row = 0; row < rows; row++) {
        free(arrayData[row]);
    }
    // Free the memory allocated for arrayData
    free(arrayData);

    return 0;
}