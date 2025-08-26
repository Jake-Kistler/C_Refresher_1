// Insertion sort in C using a Makefile for PDN 
// Jake Kistler 
// Universty of Oklahoma 

/*
At a high level this is rather simple. 
step 1: Read in input file name, output file name 
step 2: Read in integers from input file with the first number in the file being the total number of numbers that exist in the file
step 3: Sort the integers using bubble sort
step 4: Write the sorted integers to the output file with the first number again being the total numbers in the file
step 5: Free and terminate
*/

#include <stdio.h>  // file IO
#include <stdlib.h> // malloc and free come from here

// function prototypes

// Helper functions
void print_array(float *arr, int size);
// Core function
void insertion_sort(float *arr, int size);

int main(int argc, char *argv[]) 
{
    // Step 1: Read in input file name, output file name
    // checks for 2 file names and if they are not present, exits program

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }

    // input and output file paths as constants so we don't break them
    const char *input_file_path = argv[1];
    const char *output_file_path = argv[2];

    // step 2: (Try) to read in integers from input file with the first number in the file being the total number of numbers that exist in the file
    FILE *input = fopen(input_file_path, "r"); // open in read mode
    if (!input)
    {
        perror("Error opening input file");
        return 1;
    }

    int size_of_file = 0;
    if (fscanf(input, "%d", &size_of_file) != 1 || size_of_file < 0) // checks for one int being read and guards aginst negive counts being read
    {
        fprintf(stderr, "Invalid count at start of the input file.\n");
        fclose(input);
        return 1;
    }

    // Step 3: using malloc create the array that we will be sorting
    float *arr = NULL;
    if (size_of_file > 0)
    {
        // set the pointer arr (of type float) to the starting address of the memory block that will be big enough (hopefully) to hold the contents of the input file
        arr = (float *)malloc((size_t)size_of_file * sizeof(float));

        if (!arr)
        {
            fprintf(stderr, "Malloc failed for %d floats!\n" , size_of_file);
            fclose(input);
            return 1;
        }

        // now time to read the file into the array
        for (unsigned int i = 0; i < size_of_file; i++)
        {
            if (fscanf(input, "%f", &arr[i]) != 1)
            {
                fprintf(stderr, "Error reading float #%d.\n", i + 1);
                free(arr);
                fclose(input);
                return 1;
            }
        }

        // now that we have read the input file we will close it
        fclose(input);

        //call  insertion_sort
        insertion_sort(arr, size_of_file);

        // handle output file
        FILE *output = fopen(output_file_path, "w"); // open in write mode

        if(!output)
        {
            perror("Error opening the ouput file!\n");
            free(arr);
            return 1;
        }

        // print the first line (the total number of floats) to the file
        fprintf(output, "%d\n", size_of_file);

        // print the sorted array on a new line 
        for (unsigned int i = 0; i < size_of_file; i++)
        {
            fprintf(output, "%f\n", arr[i]);
        }

        fclose(output); 
        free(arr);
    }

    return 0;
}

// --------------------------------------------------------
//              Function definitions
// --------------------------------------------------------

void print_array(float *arr, int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%f\n", arr[i]);
    }
}

void insertion_sort(float *arr, int size)
{
    for (unsigned int i = 1; i < size; i++) 
    {
        float key = arr[i];
        unsigned int j = i - 1;

        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


