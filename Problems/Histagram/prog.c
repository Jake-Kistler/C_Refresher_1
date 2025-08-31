#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

  int counts[26] = {0};
  int ch;

  while ((ch = fgetc(in)) != EOF)
  {
    if (isalpha(ch))
    {
      ch = tolower(ch);
      counts[ch - 'a']++;
    }
  }

  fclose(in);

  FILE *out = fopen(outfile, "w");

  if (!out)
  {
    endProgram("Unable to open output file.");
  }

  int max = 0;

  for (int i = 0; i < 26; i++)
  {
    if (counts[i] > max) max = counts[i];
  }

  for (int level = max; level > 0; level--)
  {

    for (int i = 0; i < 26; i++)
    {
      if (counts[i] >= level)
      {
        fputc('x', out);
      }
        
      else
      {
        fputc(' ', out);
      }
        
    }

    fputc('\n', out);
  }

  for (int i = 0; i < 26; i++)
  {
    fputc('_', out);
  } 
  
  fputc('\n', out);

  for (int i = 0; i < 26; i++)
  {
    fputc('a' + i, out);
  } 

  fputc('\n', out);

  fclose(out);

  return 0;
}

void endProgram(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
