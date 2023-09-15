
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define  BUFSIZE 256



int main(void) {

    char buffer[BUFSIZE + 1];
    /* Variables */
Engine* ep = NULL; // A pointer to a MATLAB engine object
//mxArray* testArray = NULL, * result = NULL; // mxArray is the fundamental type underlying MATLAB data
mxArray* array1 = NULL;
mxArray* array2 = NULL;
mxArray* result = NULL;
//double time[3][3] = { { 1.0, 2.0, 3.0 }, {4.0, 5.0, 6.0 }, {7.0, 8.0, 9.0 } }; // Our test 'matrix', a 2-D array
double matrixOne[3][3] = { { 1.0, 2.0, 3.0 }, {4.0, 5.0, 6.0 }, {7.0, 8.0, 9.0 } }; // Our test 'matrix', a 2-D array
double matrixTwo[3][3] = { { 2.0, 2.0, 2.0 }, { 3.0, 3.0, 3.0 }, { 4.0, 4.0, 4.0 } };
/* Starts a MATLAB process */
if (!(ep = engOpen(NULL))) {
    fprintf(stderr, "\nCan't start MATLAB engine\n");
    system("pause");
    return 1;
}

//testArray = mxCreateDoubleMatrix(3, 3, mxREAL);


//memcpy((void*)mxGetPr(testArray), (void*)time, 9 * sizeof(double));
array1 = mxCreateDoubleMatrix(3, 3, mxREAL);
array2 = mxCreateDoubleMatrix(3, 3, mxREAL);
memcpy((void*)mxGetPr(array1), (void*)matrixOne, 9 * sizeof(double));
memcpy((void*)mxGetPr(array2), (void*)matrixTwo, 9 * sizeof(double));

if (engPutVariable(ep, "Array_1", array1)) {
    fprintf(stderr, "\nCannot write array1 to MATLAB \n");
    system("pause");
    exit(1); // Same as return 1;
}

if (engPutVariable(ep, "Array_2", array2)) {
    fprintf(stderr, "\nCannot write array2 to MATLAB \n");
    system("pause");
    exit(1); // Same as return 1;
}

if (engEvalString(ep, "Result = Array_1 * Array_2")) {
    fprintf(stderr, "\nError calculating eigenvalues  \n");
    system("pause");
    exit(1);
}

int row, column = 0;
printf("The first matrix was:\n");
for (column = 0; column < 3; column++)
{
    for (row = 0; row < 3; row++)
    {
        printf("%f ", matrixOne[row][column]);
    }
    printf("\n");

}
printf("The second matrix was:\n");
for (column = 0; column < 3; column++)
{
    for (row = 0; row < 3; row++)
    {
        printf("%f ", matrixTwo[row][column]);
    }
    printf("\n");

}

printf("\nRetrieving result\n");
if ((result = engGetVariable(ep, "Result")) == NULL) {
    fprintf(stderr, "\nFailed to retrieve result\n");
    system("pause");
    exit(1);
}
else {
    size_t sizeOfResult = mxGetNumberOfElements(result);
    size_t i = 0;
    printf("The matrix product is:\n");
    for (i = 0; i < (sizeOfResult / 3); ++i) {
        printf("%f ", *(mxGetPr(result) + i));
        printf("%f ", *(mxGetPr(result) + i + 3));
        printf("%f ", *(mxGetPr(result) + i + 6));
        printf("\n");

    }

}

if (engOutputBuffer(ep, buffer, BUFSIZE)) {
    fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
    system("pause");
    return 1;
}
buffer[BUFSIZE] = '\0';

engEvalString(ep, "whos"); // whos is a handy MATLAB command that generates a list of all current variables
printf("%s\n", buffer);

mxDestroyArray(array1);
mxDestroyArray(array2);
mxDestroyArray(result);
array1 = NULL;
array2 = NULL;
result = NULL;
if (engClose(ep)) {
    fprintf(stderr, "\nFailed to close MATLAB engine\n");
}

system("pause"); // So the terminal window remains open long enough for you to read it
return 0; // Because main returns 0 for successful completion
}

