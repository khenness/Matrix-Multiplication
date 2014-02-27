/*
CS3014 - CONCURRENT SYSTEMS I
Neil Hyland (11511677)
Kevin Hennessy ()
NOTE: Compile with C99 standard!
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>


// MATRIX FUNCTION PROTOTYPE(S):
void matmul(double **p_matrix_a,
            double **p_matrix_b,
            double **p_matrix_c,
            uint32_t p_size_square); // all square matrices of the same size

// TODO?
void matmul2(double **p_matrix_a,
             double **p_matrix_b,
             double **p_matrix_c,
             uint32_t p_width,
             uint32_t p_height); // all matrices have equal width & height

// TODO?
void matmul3(double **p_matrix_a,
             double **p_matrix_b,
             double **p_matrix_c,
             uint32_t p_width_a,
             uint32_t p_height_a,
             uint32_t p_width_b,
             uint32_t p_height_b,
             uint32_t p_width_c,
             uint32_t p_height_c); // all matrices have different widths & heights

#endif // MATRIX_H
