/*
CS3014 - CONCURRENT SYSTEMS I
Neil Hyland (11511677)
Kevin Hennessy ()

NOTE: Compile with C99 standard!
*/
#include "matrix.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// Matrix sizes:
int NUM_COLUMNS_A = 1000;
int NUM_ROWS_A = 1000;
int NUM_COLUMNS_B = 1000;
int NUM_ROWS_B = 1000;
int NUM_COLUMNS_C = 1000;
int NUM_ROWS_C = 1000;


// PROGRAM ENTRY POINT:
int main(int argc, char **argv)
{


	/*
	Create & initialise the matrices, then call the parallel matrix multiplication function.
	*/
	srand(time(NULL));
	printf("\nCS3014 - CONCURRENT SYSTEMS I: Matrix Multiplication Lab\n");
	printf("=======================================================================\n\n");

        /*
        Take matrix dimensions input from user
        */
        int defined = 0;
        int num;
        while(defined == 0){
           printf("\nEnter NUM_COLUMNS_A:");
           scanf("%d", &num);
           NUM_COLUMNS_A = num;
           printf("Enter NUM_ROWS_A:");
           scanf("%d", &num);
           NUM_ROWS_A = num;
           printf("Enter NUM_COLUMNS_B:");
           scanf("%d", &num);
           NUM_COLUMNS_B = num;
           printf("Enter NUM_ROWS_B:");
           scanf("%d", &num);
           NUM_ROWS_B = num;
           printf("\n");

           if(NUM_COLUMNS_A == NUM_ROWS_B){
              defined = 1;
           }else{
             printf("The product of an %d x %d matrix and an %d x %d matrix is undefined. (NUM_COLUMNS_A must equal NUM_ROWS_B) Please try again.", NUM_COLUMNS_A, NUM_ROWS_A, NUM_COLUMNS_B,NUM_ROWS_B);
           }
        }

        printf("Creating matrices and populating them with random data...\n");

	double **a = malloc(NUM_COLUMNS_A * sizeof(double*));
	double **b = malloc(NUM_COLUMNS_B * sizeof(double*));
	double **c = malloc(NUM_COLUMNS_C * sizeof(double*));

	/*
	Initialise arrays with random data...
	*/
    for(uint32_t i = 0; i < NUM_COLUMNS_A; i++)
    {
        a[i] = malloc(NUM_ROWS_A * sizeof(double));

        for(uint32_t j = 0; j < NUM_ROWS_A; j++)
        {
            // Generate pseudorandom double values:
            a[i][j] = ((double)rand() / (double)RAND_MAX) * ((double)i + (double)j);
        }
    }

    for(uint32_t i = 0; i < NUM_COLUMNS_B; i++)
    {
        b[i] = malloc(NUM_ROWS_B * sizeof(double));

        for(uint32_t j = 0; j < NUM_ROWS_B; j++)
        {
            // Generate pseudorandom double values:
            b[i][j] = ((double)rand() / (double)RAND_MAX) * ((double)i + (double)j);
        }
    }

    for(uint32_t i = 0; i < NUM_COLUMNS_C; i++)
    {
        c[i] = malloc(NUM_ROWS_B * sizeof(double));

        for(uint32_t j = 0; j < NUM_ROWS_C; j++)
        {
            // Result matrix has all doubles set to 0.0
            c[i][j] = 0.0;
        }
    }

    /*
    Print system info for OpenMP...
    */
    // TODO

    /*
    Call the matrix multiplication function...
    */
    printf("Multiplying matrices & timing the function duration...\n");

    double start_time = 0.0,
           end_time = 0.0;
           //start_ticks = 0.0,
           //end_ticks = 0.0;

    //start_ticks = omp_get_wtick();
    start_time = omp_get_wtime();

    matmul(a, b, c, NUM_COLUMNS_A);

    //end_ticks = omp_get_wtick() - start_ticks;
    end_time = omp_get_wtime() - start_time;

    /*
    Print timing information...
    */
    printf("Completed, time taken: %f seconds (from OpenMP timing system).\n", end_time);

    /*
    Garbage collection...
    */
    for(uint32_t i = 0; i < NUM_COLUMNS_A; i++) free(a[i]);
    for(uint32_t i = 0; i < NUM_COLUMNS_B; i++) free(b[i]);
    for(uint32_t i = 0; i < NUM_COLUMNS_C; i++) free(c[i]);
    free(a);
    free(b);
    free(c);

    printf("\n=======================================================================\n");
    printf("END OF PROGRAM\n\n");
	return 0;
}



