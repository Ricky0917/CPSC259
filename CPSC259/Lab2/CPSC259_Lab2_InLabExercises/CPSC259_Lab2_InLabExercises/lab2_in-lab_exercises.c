/*
 File:				lab2_in-lab_exercises.c
 Purpose:			Implementation of functions for lab 2 in-lab exercises
 Author:			Ruiqi Zang
 Student #s:	24075277
 CWLs:	      rzang01@student.ubc.ca
 Date:				September 28, 2022
 */

#include "lab2_in-lab_exercises.h"
#include <stdlib.h>
#include <string.h>

/*
 * Let's start with something easy.  There are 3 unit tests
 * for this function.
 *
 * Swaps the contents of two integer variables using pointers
 *
 * PARAM:     first_int is a pointer to an int
 * PARAM:     second_int is a pointer to an int
 * PRE:       both pointers are valid pointers to int
 * POST:      the contents of two integer variables are swapped
 * RETURN:    VOID
 */
void swap_ints(int* first_int, int* second_int)
{
	// Insert your code here
	int a=0;
	a = *first_int;
	*first_int = *second_int;
	*second_int = a;
}

/*
 * Now let's try something a little more challenging.
 *
 * Reverses the contents of the string passed to the
 * function.  Does not move the terminating null '\0'
 * character.
 *
 * PARAM:     string is a pointer to an array of char (a string)
 * PRE:       the array of char terminates with a null '\0'
 * POST:      the char array has been reversed
 * RETURN:    VOID
 */
void reverse_string(char* string)
{
	// Insert your code here
	char a = NULL;
	int i = 0;
	if (strlen(string) == 0) string = NULL;
	else {
		for (i = 0; i <= (strlen(string) - 1) / 2; i++) {
			a = string[i];
			string[i] = string[strlen(string) - 1 - i];
			string[strlen(string) - 1 - i] = a;	
		}
	}
	
	return;
}

/*
 * Let's see how well you read the lab document.
 *
 * Determines if candidate contains sample, and returns
 * 1 if  it does, and 0 if it does not.
 *
 * PARAM:     candidate is a pointer to an array of char (a string)
 * PARAM:     sample is a pointer to an array of char (a string)
 * PRE:       the arrays of char terminate with a null '\0'
 * PRE:       candidate != NULL; sample != NULL
 * POST:      N/A
 * RETURN:    IF candidate contains sample THEN 1
 *            ELSE 0.
 */
int contains_sample(char* candidate, char* sample)
{
  // Replace this return statement with your code
	int a;
	int i = 0;
	int j = 0;
	if (sample[i] == NULL) {
		a = 1;
	}
	else if (candidate[i] == NULL) {
		a = 0;
	}
	else {
		while (candidate[j] != NULL) {
			if (sample[i] == candidate[j]) {
				i++;
			}
			else {
				i = 0;
			}
			j++;

			if (i == strlen(sample))
			{
				a = 1;
				break;
			}
			else {
				a = 0;
			}
		}
	}
	
  return a;
}

/*
 * Returns the first index where sample is located inside the
 * candidate.  For example:
 * IF candidate = "Hello", sample = "Hello", RETURNS 0
 * IF candidate = "soupspoon", sample = "spoon", RETURNS 4
 * IF candidate = "ACGTACGTA", sample = "CGT", RETURNS 1
 * IF candidate = "CGTACGTA", sample = "CGTT", returns -1
 *
 * PARAM:     candidate is a pointer to an array of char (a string)
 * PARAM:     sample is a pointer to an array of char (a string)
 * PRE:       the arrays of char terminate with a null '\0'
 * POST:      N/A
 * RETURN:    IF candidate contains sample
 *            THEN the index where the first letter of sample is inside candidate
 *            ELSE -1.
 */
int find_index(char* candidate, char* sample)
{
  // Replace this return statement with your code
	int a = 0;
	int i = 0;
	if (sample[i] == NULL) {
		a = 0;
	}
	else if (strlen(candidate)<strlen(sample)) {
		a = -1;
	}
	else {
		for (i = 0; i <= strlen(candidate) - strlen(sample); i++) {
			if (strncmp(&candidate[i], sample, strlen(sample)) == 0) {
				a = i;
				break;
			}
			else {
				a = -1;
			}
		}
	}
	return a;
}