#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "smp0_tests.h"

#define LENGTH(s) (sizeof(s) / sizeof(*s))

/* Structures */

typedef struct
{

  char *word;

  int counter;

} WordCountEntry;

//WordCountEntry is a structure type , who holds 2 information. 1.*word a pointer to a character string and counter value.

int process_stream(WordCountEntry entries[], int entry_count)

{

  short line_count = 0;

  char buffer[30];

  while (gets(buffer))
  {

    if (*buffer == '.')

      break;

    /* Compare against each entry */

    int i = 0;

    //Program fix as part of question 3

    while (i <= entry_count)
    {

      if (!strcmp(entries[i].word, buffer))

        entries[i].counter++;

      i++;
    }

    line_count++;
  }

  return line_count;
}

void print_result(WordCountEntry entries[], int entry_count)

{

  int i = 0;

  printf("Result:\n");

  //Program fix as part of question 3

  while (i <= entry_count)
  {

    printf("%s:%d\n", entries[i].word, entries[i].counter);

    i++;
  }
}

//this function is called when '-h' option is used.

void printHelp(const char *name)

{

  printf("usage: %s [-h] ... \n", name);
}

int main(int argc, char **argv)

//Here argc will contain the number of argument passed and argv will contain pointer to those argument

//./main cat nap dog

//for above input argc=3, argv[0]=main, argv[1]=cat,argv[2]=nap,argv[3]=dog

{

  const char *prog_name = *argv;

  WordCountEntry entries[5];

  int entryCount = -1;

  /* Entry point for the testrunner program */

  if (argc > 1 && !strcmp(argv[1], "-test"))
  {

    run_smp0_tests(argc - 1, argv + 1);

    return EXIT_SUCCESS;
  }

  //as argv[0] contains program name itself, incrementing argv to the 1st argument value

  argv++;

  //Loop through the argv, till it encounters null value, that menas the loop will start from cat and will end after the word dog

  while (*argv != NULL)
  {

    //Check for the -h option, it checks if argv starts from '-'

    if (**argv == '-')
    {

      //Below switch case the checks the character after '-'. It is checked only if '-' option is used

      switch ((*argv)[1])
      {

      case 'h':

        printHelp(prog_name);

        //On successfully checking '-h' optin is used, functoion 'printHelp' is called

        break;

        //Note : instead of using break, we should use return EXIT_SUCCESS;

        
      default:

        printf("%s: Invalid option %s. Use -h for help.\n", prog_name, *argv);
      }
    }
    else
    {

      if (entryCount < LENGTH(entries))
      {

        entries[entryCount].word = *argv;

        //entries[entryCount++].counter = 0; addressing to the question 2. Plese check there for the explanation

        entries[entryCount].counter = 0;
      }
    }

    argv++;

  } // end while

  if (entryCount == 0)
  {

    printf("%s: Please supply at least one word. Use -h for help.\n", prog_name);

    return EXIT_FAILURE;
  }

  if (entryCount == 1)
  {

    printf("Looking for a single word\n");
  }
  else
  {

    printf("Looking for %d words\n", entryCount);
  }

  process_stream(entries, entryCount);

  print_result(entries, entryCount);

  return EXIT_SUCCESS;