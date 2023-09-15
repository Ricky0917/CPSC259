/*
 File:        main.c
 Purpose:     Interactive driver for CPSC 259 Lab2 Takehome
 Author:			Your names
 Student #s:	12345678 and 12345678
 CWLs:	      cwl1 and cwl2
 Date:				Add the date here
*/

 /******************************************************************
  DO NOT EDIT THIS FILE

  You need to understand the entire program

  Comments that start with // should be replaced with code
  Comments that are surrounded by * are hints
  ******************************************************************/

/* Preprocessor directives */
#define PROGRAM_NAME  "DNA Matcher 1.0"
#define MAX_MENU_ITEM_SIZE   32
#define NUMBER_OF_MENU_ITEMS  3
#define FIRST_MENU_ITEM       1
#define LAST_MENU_ITEM        3

#define LINESIZE            512
#define OUTPUTBUFFERLENGTH 4096

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "dna.h"

/* Forward declarations of driver supporting functions */
int    get_menu_choice(char* menu_name, char menu_items[][MAX_MENU_ITEM_SIZE], int number_of_choices);
void   clear_memory(char** sample_segment, char*** candidate_segments, int* number_of_candidates);
int    load_file(char** sample_segment, char*** candidate_segments);
void   end_program(int exit_value);
void   get_user_input(char* message, char* response);

/*
 * Main function drives the program.
 * PRE:       NULL (no pre-conditions)
 * POST:      NULL (no side-effects)
 * RETURN:    IF the program exits correctly
 *            THEN 0 ELSE 1
 */
int main(void)
{
  /* Variables */
  char* sample_segment = NULL;
  char** candidate_segments = NULL;
  char    main_menu_choices[NUMBER_OF_MENU_ITEMS][MAX_MENU_ITEM_SIZE]
    = { "1. Load file", "2. Perform analysis", "3. Exit" };
  int     number_of_candidates = 0;
  int     menu_choice = 0;
  int     number_of_main_menu_choices = NUMBER_OF_MENU_ITEMS;
  char outputstring[OUTPUTBUFFERLENGTH] = "";

  /* Generates menu and responds to user input */
  do {

    /* Prints the menu and asks the user to make a choice */
    menu_choice = get_menu_choice(PROGRAM_NAME, main_menu_choices, number_of_main_menu_choices);

    switch (menu_choice)
    {
      /* If the user chooses 1, we need to load a file */
    case 1:
      /* First clear any existing memory, then ask the user to enter the file name,
         and then try to load it */
      clear_memory(&sample_segment, &candidate_segments, &number_of_candidates);
      number_of_candidates = load_file(&sample_segment, &candidate_segments);
      break;

      /* If the user chooses 2, we want to process the file */
    case 2:
      /* But only if a file has been already loaded! */
      if (sample_segment != NULL) {
        analyze_segments(sample_segment, candidate_segments, number_of_candidates, outputstring);
        printf("%s", outputstring);
      }
      break;

      /* If the user chooses 3, we want to free dynamically allocated memory, and end the program */
    case 3:
      clear_memory(&sample_segment, &candidate_segments, &number_of_candidates);
      end_program(0);
      break;

      /* We have to have a default choice in a switch statement */
    default:
      ;
      break;
    }
  } while (1); /* Ad infinitum (1 is always true in C, 0 is always false, so while(1) is an infinite loop) */

  end_program(0);
}

/*
 * Displays a menu, asks the user to choose a menu item, and returns
 * a valid menu choice.
 *
 * Using fgets and sscanf_s ensures that we only accept correct
 * user input: an integer representing one of the numbered
 * menu items, that is neither preceded nor proceeded by any
 * additional input except for white space.
 *
 * PARAM:     Pointer to a null-terminated string representing the menu name
 * PARAM:     Array of strings (menu choices)
 * PARAM:     Number of menu choices
 * PRE:       NULL (no pre-conditions)
 * POST:      NULL (no side-effects)
 * RETURN:    INT representing valid menu choice
 */
int get_menu_choice(char* menu_name,
  char menu_choices[][MAX_MENU_ITEM_SIZE],
  int number_of_choices)
{
  /* Variable list */
  char line[BUFSIZE];
  char extra[BUFSIZE];
  int  i = 0, menu_item;

  do {
    printf("%s\n", menu_name);
    for (i = 0; i < number_of_choices; ++i) {
      printf("%s\n", menu_choices[i]);
    }
    printf("> ");

    /* If user enters EOF which is Control-C in Windows, then fgets returns a null pointer which is
       interpreted as 0.  The user probably wants to quit the program, so we clear the error in
       standard input and return the final menu item (quit, #3) */
    if (!(fgets(line, BUFSIZE, stdin))) {
      clearerr(stdin);
      return number_of_choices;
    }
  }
  /* Disallows incorrect menu choices by accepting [0, #ofchoices] and ignoring other input */
  while (sscanf_s(line, "%d%s", &menu_item, extra, BUFSIZE) != 1
    || menu_item < 0 || menu_item > number_of_choices);
  return menu_item;
}

/*
 * Clears any dynamically allocated memory and resets the candidate count.
 *
 * PARAM:     double pointer to the sample segment
 * PARAM:     triple pointer to the candidate segments
 * PARAM:     pointer to the int that stores the number of candidate segments
 * PRE:       pointers are valid pointers to dynamically allocated and populated memory
 * POST:      memory has been deallocated, number of candidates reset to 0
 * RETURN:    VOID
 */
void clear_memory(char** sample_segment, char*** candidate_segments, int* number_of_candidates)
{
  int i = 0;

  if (*sample_segment != NULL) {
    free(*sample_segment);
    *sample_segment = NULL;
  }
  if (*candidate_segments != NULL) {
    for (i = 0; i < *number_of_candidates; ++i) {
      free(*(*candidate_segments + i)); /*  Freeing triple pointers can be tricky! */
    }
    free(*candidate_segments);
    *candidate_segments = NULL;

    *number_of_candidates = 0; /* We don't want to forget to reset the candidate counter! */
  }
}

/*
 * Copies the specified file into main memory and returns the number of candidate
 * segments found.
 *
 * PARAM:     Double pointer to the sample segment
 * PARAM:     Triple pointer to a collection of candidate segments
 * PRE:       File with the user-specified name exists in the Resource Files folder
 * POST:      File has been copied to main memory
 * RETURN:    Number of candidate sequences in specified file
 */
int load_file(char** sample_segment, char*** candidate_segments)
{
  /* Variable list */
  char   file_name[BUFSIZE];
  FILE* fp = NULL;
  int    i = 0;
  int    error = 0;
  int    number_of_candidates = 0;

  /* Acquires file name from user */
  get_user_input("\nEnter file name: ", file_name);

  printf("Loading file %s\n", file_name);

  /* Opens file */
  error = fopen_s(&fp, file_name, "r");

  /* If the return value specifies that the file cannot be opened,
  prints a suitable message to standard output and returns 0 */
  if (error != 0) {
    fprintf(stderr, "File %s cannot be loaded\n", file_name);
    return 0;
  }

  /* Extracts contents of the file, and determines number of candidate segments */
  number_of_candidates = extract_dna(fp, sample_segment, candidate_segments);

  /* Closes the file and returns number of candidates extracted from the DNA */
  fclose(fp);
  return number_of_candidates;
}

/*
 * Ends the program.  Forces the system to pause first.
 * PARAM:     exit value
 * PRE:       NULL (no pre-conditions)
 * POST:      execution has ended
 * RETURN:    VOID
 */
void end_program(int exit_value)
{
  system("pause");
  exit(exit_value);
}

/*
 * Displays specified message and asks the user for a response.
 *
 * PARAM:     Pointer to a null-terminated string representing the message
 * PARAM:     Pointer to a buffer where the response will be stored
 * PRE:       Response buffer is BUFSIZE characters in size
 * POST:      Response buffer contains the user response
 * RETURN:    VOID
 */
void get_user_input(char* message, char* response)
{
  char line[BUFSIZE];

  do {
    printf("%s", message);

    /* If user enters EOF which is Control-C in Windows
       then fgets returns a null pointer which is
       interpreted as 0.  We clear the error in
       standard input and end program */
    if (!(fgets(line, BUFSIZE, stdin))) {
      clearerr(stdin);
      printf("Error acquiring user input\n");
      end_program(1);
    }
  } while (sscanf_s(line, "%s", response, BUFSIZE) != 1);

  return;
}
