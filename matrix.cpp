/* matrix.cpp */
/* starting point taken from: http://blog.speedgocomputing.com/2010/08/parallelizing-matrix-multiplication.html*/
const int size = 1000;

float a[size][size];
float b[size][size];
float c[size][size];

int main()
{
    // Initialize buffers.
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = (float)i + j;
            b[i][j] = (float)i - j;
            c[i][j] = 0.0f;
        }
    }

    // Compute matrix multiplication.
    // C <- C + A x B
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return 0;
}