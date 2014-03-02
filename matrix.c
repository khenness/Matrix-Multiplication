/*
CS3014 - CONCURRENT SYSTEMS I
Neil Hyland (11511677)
Kevin Hennessy (11726665)
NOTE: Compile with C99 standard!
*/
#include "matrix.h"

#include <omp.h>


// All square matrices
void matmul(double **p_matrix_a,
            double **p_matrix_b,
            double **p_matrix_c,
            uint32_t p_size_square)
{
    /*
    Compute the matrix multiplication of two matrices A and B, and store the result in matrix C.
    e.g. C = C + A * B
    This function is timed with the OpenMP timing system.
    */
    #pragma omp parallel for default(none) shared(p_matrix_a, p_matrix_b, p_matrix_c, p_size_square)
    for(uint32_t i = 0; i < p_size_square; ++i)
    {
        for(uint32_t j = 0; j < p_size_square; ++j)
        {
            double current_sum = 0.0;
            for(uint32_t k = 0; k < p_size_square; ++k)
            {
                current_sum += p_matrix_a[i][k] * p_matrix_b[k][j];
            }

            p_matrix_c[i][j] = current_sum;
        }
    }
}


// Equal widths & heights
void matmul2(double **p_matrix_a,
             double **p_matrix_b,
             double **p_matrix_c,
             uint32_t p_width,
             uint32_t p_height)
{
    // TODO?
}


// All different widths & heights
void matmul3(double **p_matrix_a,
             double **p_matrix_b,
             double **p_matrix_c,
             uint32_t p_width_a,
             uint32_t p_height_a,
             uint32_t p_width_b,
             uint32_t p_height_b,
             uint32_t p_width_c,
             uint32_t p_height_c)
{
    // TODO?
}


