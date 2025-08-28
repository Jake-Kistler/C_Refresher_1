// Merge sort in C using a Makefile for PDN 
// Jake Kistler 
// Universty of Oklahoma 

/*
At a high level this is rather simple. 
step 1: Read in input file name, output file name 
step 2: Read in integers from input file with the first number in the file being the total number of numbers that exist in the file
step 3: Sort the integers using selection sort
step 4: Write the sorted integers to the output file with the first number again being the total numbers in the file
step 5: Free and terminate
*/

#include <stdio.h>  // file IO
#include <stdlib.h> // malloc and free come from here

// function prototypes

// Helper functions
void print_array(float *arr, int size);
// Core function
void merge(float *arr, int left, int middle, int right);
void merge_sort(float *arr, int left, int right);

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

        //call merge_sort
        merge_sort(arr, 0, size_of_file - 1);

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

void merge(float *arr, int left, int middle, int right)
{
    int length_of_left_subarray = middle - left + 1;
    int length_of_right_subarray = right - middle;

    // create temp arrays
    float *left_subarray = (float *)malloc(length_of_left_subarray * sizeof(float));
    float *right_subarray = (float *)malloc(length_of_right_subarray * sizeof(float));

    // copy data to temp arrays
    for(unsigned int i = 0; i < length_of_left_subarray; i++)
    {
        left_subarray[i] = arr[left + i];
    }

    for(unsigned int j = 0; j < length_of_right_subarray; j++)
    {
        right_subarray[j] = arr[middle + 1 + j];
    }

    // merge the temp arrays back into arr[left..right]

    int index_of_left_subarray = 0; // initial index of first subarray
    int index_of_right_subarray = 0; // initial index of second subarray
    int index_of_merged_array = left; // initial index of merged subarray

    while(index_of_left_subarray < length_of_left_subarray && index_of_right_subarray < length_of_right_subarray)
    {
        if(left_subarray[index_of_left_subarray] <= right_subarray[index_of_right_subarray])
        {
            arr[index_of_merged_array] = left_subarray[index_of_left_subarray];
            index_of_left_subarray++;
        }
        else
        {
            arr[index_of_merged_array] = right_subarray[index_of_right_subarray];
            index_of_right_subarray++;
        }
        index_of_merged_array++;
    }

    //  copy the remaining elements of left_subarray, if there are any
    while(index_of_left_subarray < length_of_left_subarray)
    {
        arr[index_of_merged_array] = left_subarray[index_of_left_subarray];
        index_of_left_subarray++;
        index_of_merged_array++;
    }

    // copy the remaining elements of right_subarray, if there are any
    while(index_of_right_subarray < length_of_right_subarray)
    {
        arr[index_of_merged_array] = right_subarray[index_of_right_subarray];
        index_of_right_subarray++;
        index_of_merged_array++;
    }

}

void merge_sort(float *arr, int left, int right)
{
    if(left < right)
    {
        int middle = left + (right - left) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }

}




