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
#define MATRIX_WIDTH_A 1000
#define MATRIX_HEIGHT_A 1000
#define MATRIX_WIDTH_B 1000
#define MATRIX_HEIGHT_B 1000
#define MATRIX_WIDTH_C 1000
#define MATRIX_HEIGHT_C 1000


// PROGRAM ENTRY POINT:
int main(int argc, char **argv)
{
	/*
	Create & initialise the matrices, then call the parallel matrix multiplication function.
	*/
	srand(time(NULL));
	printf("\nCS3014 - CONCURRENT SYSTEMS I: Matrix Multiplication Lab\n");
	printf("=======================================================================\n\n");
    printf("Creating matrices and populating them with random data...\n");

	double **a = malloc(MATRIX_WIDTH_A * sizeof(double*));
	double **b = malloc(MATRIX_WIDTH_B * sizeof(double*));
	double **c = malloc(MATRIX_WIDTH_C * sizeof(double*));

	/*
	Initialise arrays with random data...
	*/
    for(uint32_t i = 0; i < MATRIX_WIDTH_A; i++)
    {
        a[i] = malloc(MATRIX_HEIGHT_A * sizeof(double));

        for(uint32_t j = 0; j < MATRIX_HEIGHT_A; j++)
        {
            // Generate pseudorandom double values:
            a[i][j] = ((double)rand() / (double)RAND_MAX) * ((double)i + (double)j);
        }
    }

    for(uint32_t i = 0; i < MATRIX_WIDTH_B; i++)
    {
        b[i] = malloc(MATRIX_HEIGHT_B * sizeof(double));

        for(uint32_t j = 0; j < MATRIX_HEIGHT_B; j++)
        {
            // Generate pseudorandom double values:
            b[i][j] = ((double)rand() / (double)RAND_MAX) * ((double)i + (double)j);
        }
    }

    for(uint32_t i = 0; i < MATRIX_WIDTH_C; i++)
    {
        c[i] = malloc(MATRIX_HEIGHT_B * sizeof(double));

        for(uint32_t j = 0; j < MATRIX_HEIGHT_C; j++)
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

    matmul(a, b, c, MATRIX_WIDTH_A);

    //end_ticks = omp_get_wtick() - start_ticks;
    end_time = omp_get_wtime() - start_time;

    /*
    Print timing information...
    */
    printf("Completed, time taken: %f seconds (from OpenMP timing system).\n", end_time);

    /*
    Garbage collection...
    */
    for(uint32_t i = 0; i < MATRIX_WIDTH_A; i++) free(a[i]);
    for(uint32_t i = 0; i < MATRIX_WIDTH_B; i++) free(b[i]);
    for(uint32_t i = 0; i < MATRIX_WIDTH_C; i++) free(c[i]);
    free(a);
    free(b);
    free(c);

    printf("\n=======================================================================\n");
    printf("END OF PROGRAM\n\n");
	return 0;
}



