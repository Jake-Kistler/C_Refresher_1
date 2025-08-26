// Bubble sort in C using a Makefile for PDN 
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

#include <stdio.h>
#include <stdlib.h>


// function prototypes

// Helper functions
void print_array(float *arr, int size);
// Core function
void bubble_sort(float *arr, int size);

int main(int argc, char *argv[]) 
{
    // Step 1: Read in input file name, output file name
    // checks for 2 file names and if they are not present, exits program
    /*
    in cpp this looks like:
    if(argc <3)
    {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.txt>" << std::endl;
        return 1;
    //}
    */

    if (argc < 3)
    {
        printf(stderr, "Usage: %s <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }

    // input and output file paths as constants so we don't break them
    const char *input_file_path = argv[1];
    const char *output_file_path = argv[2];
    


    return 0;
}

