<div align="center">

<h3 align="center">Data Processing Utility</h3>

  <p align="center">
    A C command-line utility to clean two-dimensional floating-point data for machine learning.
    <br />
     <a href="https://github.com/tridibbanik17/data_processing_assignment">github.com/tridibbanik17/data_processing_assignment</a>
  </p>
</div>

## Table of Contents

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#key-features">Key Features</a></li>
      </ul>
    </li>
    <li><a href="#architecture">Architecture</a></li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
      </ul>
    </li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## About The Project

This repository contains a command-line utility named `clean`, written in C, designed to process two-dimensional grids of floating-point numbers. It is specifically tailored for cleaning data intended for machine learning applications by handling missing or invalid values. The utility provides two primary cleaning strategies: imputation (replacing NaN values with column averages) and deletion (removing rows containing NaN values).

### Key Features

- **NaN Value Imputation:** Replaces Not-a-Number (NaN) values within each column with the average of the valid floating-point numbers in that column. If a column contains only NaN values, it will be replaced with a default value of 0.0.
- **Row Deletion:** Removes any row that contains one or more NaN values, providing a dataset free of missing data.
- **Command-Line Interface:** Offers a simple command-line interface for easy integration into data processing pipelines.
- **Standard Input/Output:** Reads data from standard input and writes the cleaned data to standard output, facilitating flexible data handling.
- **Error Handling:** Includes basic error handling for invalid input data, such as incorrect row or column counts.

## Architecture

The project is written in C and consists of the following files:

- `clean.c`: Contains the main function and the implementation of the data cleaning algorithms (imputation and deletion) and output functions.
- `clean.h`: Header file containing function prototypes, macro definitions for maximum grid size, default values, output precision, command-line arguments, and usage messages.
- `read_data.c`: Contains the function to read the data from standard input and create the two-dimensional array.
- `read_data.h`: Header file containing the function prototype for `read_data` and macro definitions for maximum grid size and invalid float values.
- `makefile`: Used to compile the C source files into an executable.
- `.github/workflows/build.yml`: GitHub Actions workflow file for continuous integration, automating the build and testing process.

The program flow is as follows:

1.  The `read_data` function reads the number of rows and columns from standard input, allocates memory for the 2D array, and populates it with data from standard input. Invalid input is replaced with `NAN`.
2.  The `main` function in `clean.c` parses command-line arguments.
    *   If no arguments are provided, the `clean_impute` function is called to replace `NAN` values with column averages.
    *   If the `-d` argument is provided, the `clean_delete` function is called to remove rows containing `NAN` values.
    *   If invalid arguments are provided, a usage message is printed.
3.  The `output_data` function prints the cleaned data to standard output, including the number of rows and columns followed by the data grid.
4.  Memory allocated for the 2D array is freed before the program exits.

## Getting Started

### Prerequisites

-   A C compiler (e.g., GCC)
-   Make

### Installation

1.  Clone the repository:

    ```sh
    git clone https://github.com/tridibbanik17/data_processing_assignment.git
    ```

2.  Navigate to the repository directory:

    ```sh
    cd data_processing_assignment
    ```

3.  Compile the code using Make:

    ```sh
    make
    ```

### Usage

1.  **Imputation (Replace NaN values with column averages):**

    ```sh
    ./clean < input_file.txt > output_file.txt
    ```

2.  **Deletion (Remove rows containing NaN values):**

    ```sh
    ./clean -d < input_file.txt > output_file.txt
    ```

    Where `input_file.txt` contains the data in the following format:

    ```
    <number_of_rows> <number_of_columns>
    <row_1_col_1> <row_1_col_2> ... <row_1_col_n>
    <row_2_col_1> <row_2_col_2> ... <row_2_col_n>
    ...
    <row_m_col_1> <row_m_col_2> ... <row_m_col_n>
    ```
   Example `wbcd.txt` input:
   ```
   569 30
   17.99 NAN 122.8 1001 0.1184 0.2776 NAN 0.1471 0.2419 0.07871 1.095 0.9053 8.589 153.4 0.006399 0.04904 0.05373 0.01587 0.03003 0.006193 25.38 17.33 184.6 2019 0.1622 0.6656 0.7119 0.2654 0.4601 0.1189
   20.57 17.77 132.9 1326 0.08474 0.07864 0.0869 0.07017 0.1812 0.05667 0.5435 0.7339 3.398 74.08 0.005225 0.01308 0.0186 0.0134 0.01389 0.003532 24.99 23.41 158.8 1956 0.1238 0.1866 0.2416 0.186 0.275 0.08902
   19.69 21.25 130 1203 0.1096 0.1599 0.1974 0.1279 0.2069 0.05999 0.7456 0.7869 4.585 94.03 0.00615 0.04006 0.03832 0.02058 0.0225 0.004571 23.57 25.53 152.5 1709 0.1444 0.4245 0.4504 0.243 0.3613 0.08758
   11.42 20.38 77.58 386.1 0.1425 0.2839 0.2414 0.1052 0.2597 0.09744 0.4956 1.156 3.445 27.23 0.00911 0.07458 0.05661 0.01867 0.05963 0.009208 14.91 26.5 98.87 567.7 0.2098 0.8663 0.6869 0.2575 0.6638 0.173
   20.29 14.34 135.1 1297 0.1003 0.1328 0.198 0.1043 0.1809 0.05883 0.7572 0.7813 5.438 94.44 0.01149 0.02461 0.05688 0.01885 0.01756 0.005115 22.54 16.67 152.2 1575 0.1374 0.205 0.4 0.1625 0.2364 0.07678
   ```

## Acknowledgments

- This README was created using [gitreadme.dev](https://gitreadme.dev) — an AI tool that looks at your entire codebase to instantly generate high-quality README files.
