// Merge sort in C using a Makefile for PDN
// Jake Kistler
// University of Oklahoma

/*
At a high level this is rather simple.
step 1: Read in input file name, output file name
step 2: Read in floats from input file with the first number in the file being the total number of numbers that exist in the file
step 3: Sort the floats using merge sort
step 4: Write the sorted floats to the output file with the first number again being the total numbers in the file
step 5: Free and terminate
*/

#include <stdio.h>   // file IO
#include <stdlib.h>  // malloc and free
#include <errno.h>   // perror

// function prototypes

// Helper functions
void print_array(float *arr, int size);

// Core functions
static void merge_sort(float *arr, int size);
static void merge_sort_rec(float *arr, float *tmp, int left, int right);
static void merge_ranges(float *arr, float *tmp, int left, int mid, int right);

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

    // Step 2: (Try) to read in floats from input file with the first number as the total count
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

    // Step 3: merge sort
    if (size_of_file > 1)
    {
        merge_sort(arr, size_of_file);
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

static void merge_ranges(float *arr, float *tmp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid)  tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];

    for (int t = left; t <= right; t++)
    {
        arr[t] = tmp[t];
    }
}

static void merge_sort_rec(float *arr, float *tmp, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    merge_sort_rec(arr, tmp, left, mid);
    merge_sort_rec(arr, tmp, mid + 1, right);
    merge_ranges(arr, tmp, left, mid, right);
}

static void merge_sort(float *arr, int size)
{
    float *tmp = (float *)malloc((size_t)size * sizeof(float));
    if (!tmp)
    {
        fprintf(stderr, "Malloc failed for merge temp of %d floats!\n", size);
        return; // graceful: avoid crash; caller still writes output
    }
    merge_sort_rec(arr, tmp, 0, size - 1);
    free(tmp);
}
