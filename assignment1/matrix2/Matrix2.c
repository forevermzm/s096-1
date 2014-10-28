#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 30
#define EXIT_FAILURE 1

typedef struct Matrix_s
{
    size_t R, C;
    int *index;
} Matrix;

void initMatrix(Matrix *m, int row, int col)
{
    m->R = row;
    m->C = col;
    // Use a 1D array as a 2D matrix.
    m->index = (int *) malloc(sizeof(int) * row * col);
}

void setElement(Matrix *m, int row, int col, int element)
{
    m->index[row * (m->C) + col] = element;
}

int getElement(Matrix *m, int row, int col)
{
    return m->index[row * (m->C) + col];
}

void destroyMatrix(Matrix *m)
{
    m->R = 0;
    m->C = 0;
    free(m->index);
}

void read_in_matrix(Matrix *m, FILE *fp)
{
    fscanf( fp, "%zu %zu", &m->R, &m->C );

    initMatrix(m, m->R, m->C);
    for ( size_t r = 0; r < m->R; ++r )
    {
        for ( size_t c = 0; c < m->C; ++c )
        {
            int element;
            fscanf( fp, "%d", &element );
            setElement(m, r, c, element);
        }
    }
}

void multiplyMatrix(Matrix *m1, Matrix *m2, Matrix *result)
{
    result->R = m1->R;
    result->C = m2->C;
    int nRows = result->R,
        nCols = result->C;

    int row, col;
    for (row = 0 ; row < nRows ; row ++)
    {
        for (col = 0 ; col < nCols ; col ++)
        {
            int i, temp = 0;
            size_t nInner = m1->C;
            for (i = 0 ; i < nInner ; i ++)
            {
                temp += m1->index[row * nInner + i] * m2->index[i * nCols + col];
            }
            result->index[row * nCols + col] = temp;
        }
    }
}

void printMatrix(Matrix *m)
{
    int i, j;
    printf("%zu %zu\n", m->R, m->C);
    for ( i = 0 ; i < m->R ; i ++ )
    {
        for ( j = 0 ; j < m->C ; j ++ )
        {
            printf("%d", getElement(m, i, j));
            if (j != m->C - 1 )
                printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: Matrix <matrix_input>");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen( argv[1],  "r" );

    if (fp == NULL)
    {
        printf("File %s not found.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    Matrix m1, m2, result;

    read_in_matrix(&m1, fp);
    read_in_matrix(&m2, fp);
    fclose(fp);

    if (m1.C != m2.R)
    {
        initMatrix(&result, 0, 0);
    }
    else
    {
        initMatrix(&result, m1.R, m2.C);
        multiplyMatrix(&m1, &m2, &result);
    }

    // printMatrix(&result);
    destroyMatrix(&m1);
    destroyMatrix(&m2);
    destroyMatrix(&result);
    return 0;
}