// Function prototypes for clean_impute(), clean_delete() and output_data() functions found from clean.c

#include <math.h>

// Maximum grid size
#define MAX_ROWS 1000
#define MAX_COLS 1000

// Default value for imputation
#define DEFAULT_VALUE 0.0

// Output precision for floating-point numbers
#define OUTPUT_PRECISION "%.3f"

// Command-line arguments
#define DELETE_MODE "-d"

// Usage message
#define USAGE_MESSAGE "Usage: ./clean [-d]\n"

// Function prototypes
void clean_impute(float **arrayData, int rows, int cols);
float **clean_delete(float **arrayData, int rows, int cols, int *new_rows);
void output_data(float **arrayData, int rows, int cols);


