#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function prototypes
void endProgram(const char *message);
double arr_min(const double *arr, int size);
double arr_max(const double *arr, int size);
double arr_sum(const double *arr, int size);
double arr_mean(const double *arr, int size);
double arr_standard_dev(const double *arr, int size, double mean);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        endProgram("Usage: ./prog <input file> <output file>");
    }

    // get file names from command line arguments
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];

    // try for input file
    FILE *inputFile = fopen(inputFileName, "r");
    
    if (!inputFile)
    {
        endProgram("Error: Unable to open input file.");
    }

    int size = 0;

    if (fscanf(inputFile, "%d", &size) != 1 || size <= 0)
    {
        fclose(inputFile);
        endProgram("Error: Invalid size in input file.");
    }

    // allocate memory for data
    double *data = (double *)malloc(sizeof(double) * size);

    // check memory allocation
    if (!data)
    {
        fclose(inputFile);
        endProgram("Error: Memory allocation failed.");
    }

    // read data from file
    for (int i = 0; i < size; i++)
    {
        if (fscanf(inputFile, "%lf", &data[i]) != 1) // check for read error
        {
            free(data);
            fclose(inputFile);
            endProgram("Error: Invalid data in input file.");
        }
    }
    fclose(inputFile);

    // calculate statistics
    double min_value = arr_min(data, size);
    double max_value = arr_max(data, size);
    double mean_value = arr_mean(data, size);
    double standard_dev_value = arr_standard_dev(data, size, mean_value);

    // try for output file
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile)
    {
        free(data);
        endProgram("Error: Unable to open output file.");
    }

    fprintf(outputFile, "Minimum: %.2lf\n", min_value);
    fprintf(outputFile, "Maximum: %.2lf\n", max_value);
    fprintf(outputFile, "Mean: %.2lf\n", mean_value);
    fprintf(outputFile, "Standard Deviation: %.2lf\n", standard_dev_value);

    // clean up and leave
    fclose(outputFile);
    free(data);

    return 0;
}

//  function definitions
void endProgram(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

double arr_min(const double *arr, int size)
{
    double min = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

double arr_max(const double *arr, int size)
{
    double max = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

double arr_sum(const double *arr, int size)
{
    double sum = 0.0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

double arr_mean(const double *arr, int size)
{
    return arr_sum(arr, size) / size;
}

double arr_standard_dev(const double *arr, int size, double mean)
{
    double sum_squared_diff = 0.0;

    for (int i = 0; i < size; i++)
    {
        double diff = arr[i] - mean;
        sum_squared_diff += diff * diff;
    }

    return sqrt(sum_squared_diff / size);
}
