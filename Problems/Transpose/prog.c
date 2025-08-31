#include <stdio.h>
#include <stdlib.h>


void endProgram(const char *message);

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    endProgram("Usage: ./prog <input file> <output file>");
  }

  const char *infile = argv[1];
  const char *outfile = argv[2];

  FILE *in = fopen(infile, "r");

  if (!in)
  {
    endProgram("Unable to open input file.");
  }

  int rows, cols;

  if (fscanf(in, "%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0)
  {
    fclose(in);
    endProgram("Invalid matrix dimensions.");
  }

  double *data = malloc(sizeof(double) * rows * cols);

  if (!data)
  {
    fclose(in);
    endProgram("malloc failed");
  }

  for (int r = 0; r < rows; r++)
  {

    for (int c = 0; c < cols; c++)
    {

      if (fscanf(in, "%lf", &data[r * cols + c]) != 1)
      {

        free(data);
        fclose(in);
        endProgram("Invalid matrix data.");
      }

    }
  }

  fclose(in);

  FILE *out = fopen(outfile, "w");

  if (!out)
  {
    free(data);
    endProgram("Unable to open output file.");
  }

  fprintf(out, "%d %d\n", cols, rows);

  for (int c = 0; c < cols; c++)
  {

    for (int r = 0; r < rows; r++)
    {
      fprintf(out, "%.15g", data[r * cols + c]);
      if (r + 1 < rows) fprintf(out, " ");
    }

    fprintf(out, "\n");
  }

  free(data);
  fclose(out);

  return 0;
}

void endProgram(const char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
