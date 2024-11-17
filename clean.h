// Function prototypes for clean_impute(), clean_delete() and output_data() functions found from clean.c

void clean_impute(float **arrayData, int rows, int cols);
float **clean_delete(float **arrayData, int rows, int cols, int *new_rows);
void output_data(float **arrayData, int rows, int cols);