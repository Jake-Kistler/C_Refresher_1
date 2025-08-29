// Quick sort in C using a Makefile for PDN
// Jake Kistler
// University of Oklahoma

/*
At a high level this is rather simple.
step 1: Read in input file name, output file name
step 2: Read in floats from input file with the first number in the file being the total number of numbers that exist in the file
step 3: Sort the floats using quick sort
step 4: Write the sorted floats to the output file with the first number again being the total numbers in the file
step 5: Free and terminate
*/

#include <stdio.h>   // file IO
#include <stdlib.h>  // malloc and free
#include <errno.h>   // perror

// function prototypes

// Helper functions
void print_array(float *arr, int size);
static void swap(float *a, float *b);

// Core functions
static int partition(float *arr, int low, int high);
static void quick_sort(float *arr, int low, int high);

int main(int argc, char *argv[])
{
    // Step 1: Read in input file name, output file name
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }

    const char *input_file_path = argv[1];
    const char *output_file_path = argv[2];

    // Step 2: (Try) to read in floats from input file with count on first line
    FILE *input = fopen(input_file_path, "r");
    if (!input)
    {
        perror("Error opening input file");
        return 1;
    }

    int size_of_file = 0;
    if (fscanf(input, "%d", &size_of_file) != 1 || size_of_file < 0)
    {
        fprintf(stderr, "Invalid count at start of the input file.\n");
        fclose(input);
        return 1;
    }

    float *arr = NULL;
    if (size_of_file > 0)
    {
        arr = (float *)malloc((size_t)size_of_file * sizeof(float));
        if (!arr)
        {
            fprintf(stderr, "Malloc failed for %d floats!\n", size_of_file);
            fclose(input);
            return 1;
        }

        for (int i = 0; i < size_of_file; i++)
        {
            if (fscanf(input, "%f", &arr[i]) != 1)
            {
                fprintf(stderr, "Error reading float #%d.\n", i + 1);
                free(arr);
                fclose(input);
                return 1;
            }
        }
    }
    fclose(input);

    // Step 3: quick sort
    if (size_of_file > 1)
    {
        quick_sort(arr, 0, size_of_file - 1);
    }

    // Step 4: write output
    FILE *output = fopen(output_file_path, "w");
    if (!output)
    {
        perror("Error opening the output file");
        free(arr);
        return 1;
    }

    fprintf(output, "%d\n", size_of_file);
    for (int i = 0; i < size_of_file; i++)
    {
        fprintf(output, "%f\n", arr[i]);
    }

    fclose(output);
    free(arr);

    // Step 5: terminate
    return 0;
}

// --------------------------------------------------------
//              Function definitions
// --------------------------------------------------------

void print_array(float *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%f\n", arr[i]);
    }
}

static void swap(float *a, float *b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

static int partition(float *arr, int low, int high)
{
    float pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void quick_sort(float *arr, int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}
