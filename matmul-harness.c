//test

/* Test and timing harness program for developing a dense matrix
	 multiplication routine for the CS3014 module */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <assert.h>

// OpenMP
#include <omp.h>


/* the following two definitions of DEBUGGING control whether or not
	 debugging information is written out. To put the program into
	 debugging mode, uncomment the following line: */
//#define DEBUGGING(_x) _x
/* to stop the printing of debugging information, use the following line: */
#define DEBUGGING(_x)


/* write matrix to stdout */
void write_out(double ** a, int dim1, int dim2)
{
	int i, j;

	for ( i = 0; i < dim1; i++ ) {
		for ( j = 0; j < dim2 - 1; j++ ) {
			printf("%f, ", a[i][j]);
		}
		printf("%f\n", a[i][dim2-1]);
	}
}


/* create new empty matrix */
double ** new_empty_matrix(int dim1, int dim2)
{
	double ** result = malloc(sizeof(double*) * dim1);
	double * new_matrix = malloc(sizeof(double) * dim1 * dim2);

	int i;

	for ( i = 0; i < dim1; i++ ) {
		result[i] = &(new_matrix[i*dim2]);
	}

	return result;
}

/* take a copy of the matrix and return in a newly allocated matrix */
double ** copy_matrix(double ** source_matrix, int dim1, int dim2)
{
	int i, j;
	double ** result = new_empty_matrix(dim1, dim2);

	for ( i = 0; i < dim1; i++ ) {
		for ( j = 0; j < dim2; j++ ) {
			result[i][j] = source_matrix[i][j];
		}
	}

	return result;
}

/* create a matrix and fill it with random numbers */
double ** gen_random_matrix(int dim1, int dim2)
{
	double ** result;
	int i, j;
	struct timeval seedtime;
	int seed;

	result = new_empty_matrix(dim1, dim2);

	/* use the microsecond part of the current time as a pseudorandom seed */
	gettimeofday(&seedtime, NULL);
	seed = seedtime.tv_usec;
	srand(seed);

	/* fill the matrix with random numbers */
	for ( i = 0; i < dim1; i++ ) {
		for ( j = 0; j < dim2; j++ ) {
			long long upper = rand();
			long long lower = rand();
			result[i][j] = (double)((upper << 32) | lower);
		}
	}

	return result;
}

/* check the sum of absolute differences is within reasonable epsilon */
void check_result(double ** result, double ** control, int dim1, int dim2)
{
/*
Modified to check exact matrix values (no allowance for small variations).
*/
	int i, j;
  	int error = 0;

  	for ( i = 0; i < dim1; i++ )
  	{
    	for ( j = 0; j < dim2; j++ )
    	{
			if(control[i][j] != result[i][j]){
				error = 1;
			}
    	}
  	}

	if(error == 1)
	{
		printf("Matrices do not match!\n");
	}
}

/* multiply matrix A times matrix B and put result in matrix C */
void matmul(double ** A, double ** B, double ** C, int a_dim1, int a_dim2, int b_dim2)
{
	int i = 0,
		j = 0,
		k = 0;

	for (i = 0; i < a_dim1; i++ ) {
		for (j = 0; j < b_dim2; j++ ) {
			double sum = 0.0;
			for ( k = 0; k < a_dim2; k++ ) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}
}


/* the fast version of matmul written by the team */
void team_matmul(double **restrict A, double **restrict B, double **restrict C, int p_a_dim1, int p_a_dim2, int p_b_dim2)
/*
CS3014 Assignment 1 - Matrix Multiplication Function

NEIL HYLAND (11511677)
KEVIN HENNESSY (11726665)

"stdint.h"'s uint32_t used as a fixed-width unsigned 32-bit integer value.
"omp.h"'s pragmas are used to parallelise many of the applicable for loops.
Large matrices are multiplied with a transpose matrix created from operand matrix B to allow better cache access.

*/
{
	/*
	Store local register versions of the dimension variables:
	*/
	register uint32_t a_dim1 = p_a_dim1,
			 		  a_dim2 = p_a_dim2,
			 		  b_dim2 = p_b_dim2;
	

    if(a_dim1 < 50 && a_dim2 < 50 && b_dim2 < 50)
    {
        /*
        Use the original (non-parallel) multiplication algorithm if
        the dimensions are too small that OMP parallelisation yields no
        faster runtime.
        */
        for(uint32_t i = 0; i < a_dim1; i++)
        {
            for(uint32_t j = 0; j < b_dim2; j++)
            {
                double temp_sum = 0.0,
                	   a_temp = 0.0,
                	   b_temp = 0.0;

                for(uint32_t k = 0; k < a_dim2; k++)
                {
                	a_temp = A[i][k];
                	b_temp = B[k][j];
                
                    temp_sum += a_temp * b_temp;
                }

                C[i][j] = temp_sum;
            }
        }
    }
    else if(a_dim1 < 200 && a_dim2 < 200 && b_dim2 < 200)
    {
        /*
        Small to small/medium matrix sizes are less efficient with transpose multiplication, so
        use OMP-parallelised version of the standard/original algorithm
        */
        #pragma omp parallel for collapse(2)
        for(uint32_t i = 0; i < a_dim1; i++)
        {
            for(uint32_t j = 0; j < b_dim2; j++)
            {
                double temp_sum = 0.0,
                	   a_temp = 0.0,
                	   b_temp = 0.0;

                for(uint32_t k = 0; k < a_dim2; k++)
                {
                    a_temp = A[i][k],
                    b_temp = B[k][j];

                    temp_sum += a_temp * b_temp;
                }

                C[i][j] = temp_sum;
            }
        }
    }
    else
    {
        /*
        Create a transpose matrix from matrix operand B (allowed to store more of the matrix on the cache).
        */
        double **T = malloc(sizeof(double*) * b_dim2);

		/*
		Create/allocate arrays (with simple OMP parallelisation).
		*/
        #pragma omp parallel for
        for(uint32_t i = 0; i < b_dim2; i++)
        {
            double *temp_ptr = malloc(sizeof(double) * a_dim2);
            T[i] = temp_ptr;
        }
        
        /*
        Create transposed matrix elements (with simple OMP parallelisation).
        */
        #pragma omp parallel for
        for(uint32_t i = 0; i < a_dim2; i++)
        {
        	double temp = 0.0;
        	
        	for(uint32_t j = 0; j < b_dim2; j++)
        	{
        		temp = B[i][j];
            	T[j][i] = temp;
            }
        }

		/*
		Perform the matrix multiplication (with OMP parallelisation on the first two for loops).
		*/
        #pragma omp parallel for collapse(2)
        for(uint32_t i = 0; i < a_dim1; i++)
        {
            for(uint32_t j = 0; j < b_dim2; j++)
            {
                double temp_sum = 0.0,
                	   a_temp = 0.0,
                	   b_temp = 0.0;

                for(uint32_t k = 0; k < a_dim2; k++)
                {
                    a_temp = A[i][k];
                    
                    /*
                    Reversing k & j from original algorithm due to the transpose matrix multiplication.
                    */
                    b_temp = T[j][k];
                    
                    temp_sum += a_temp * b_temp;
                }

                C[i][j] = temp_sum;
            }
        }

		/*
		Dispose & garbage collect the transpose matrix (with simple OMP parallelisation).
		*/
        #pragma omp parallel for
        for(uint32_t i = 0; i < b_dim2; i++)
        {
            double *temp_ptr = T[i];
            free(temp_ptr);
        }
        free(T);
    }
}


int main(int argc, char ** argv)
{
	double ** A, ** B, ** C;
	double ** control_matrix;
	long long mul_time;
	int a_dim1, a_dim2, b_dim1, b_dim2;
	struct timeval start_time;
	struct timeval stop_time;

	if ( argc != 5 ) {
		fprintf(stderr, "Usage: matmul-harness <A nrows> <A ncols> <B nrows> <B ncols>\n");
		exit(1);
	}
	else {
		a_dim1 = atoi(argv[1]);
		a_dim2 = atoi(argv[2]);
		b_dim1 = atoi(argv[3]);
		b_dim2 = atoi(argv[4]);
	}

	/* check the matrix sizes are compatible */
	if ( a_dim2 != b_dim1 ) {
		fprintf(stderr,
			"FATAL number of columns of A (%d) does not match number of rows of B (%d)\n",
			a_dim2, b_dim1);
		exit(1);
	}

	/* allocate the matrices */
	A = gen_random_matrix(a_dim1, a_dim2);
	B = gen_random_matrix(b_dim1, b_dim2);
	C = new_empty_matrix(a_dim1, b_dim2);
	control_matrix = new_empty_matrix(a_dim1, b_dim2);

	DEBUGGING(write_out(A, a_dim1, a_dim2));

	/* use a simple matmul routine to produce control result */
	matmul(A, B, control_matrix, a_dim1, a_dim2, b_dim2);

	/* record starting time */
	gettimeofday(&start_time, NULL);

	/* perform matrix multiplication */
	team_matmul(A, B, C, a_dim1, a_dim2, b_dim2);

	/* record finishing time */
	gettimeofday(&stop_time, NULL);
	mul_time = (stop_time.tv_sec - start_time.tv_sec) * 1000000L +
		(stop_time.tv_usec - start_time.tv_usec);
	printf("Matmul time: %lld microseconds\n", mul_time);

	DEBUGGING(write_out(C, a_dim1, b_dim2));

	/* now check that the team's matmul routine gives the same answer
		 as the known working version */
	check_result(C, control_matrix, a_dim1, b_dim2);

	return 0;
}

