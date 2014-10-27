#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 30
#define MAXN 300
#define EXIT_FAILURE 1

typedef struct Matrix_s
{
    size_t R, C;
    int index[MAXN][MAXN];
} Matrix;

void parseMatrixSize(char const *line, Matrix *m)
{
    int i,
        len = strlen(line),
        size;
    char *N = malloc(5);
    for (i = 0 ; i < len ; i ++)
    {
        if (line[i] == ' ')
        {
            strncpy(N, line, i);
            // printf("%s\n", N);
            sscanf(N, "%d", &size);
            m->R = size;

            strncpy(N, i + 1 + line, len - i - 1);
            // printf("%s\n", N);
            sscanf(N, "%d", &size);
            m->C = size;
        }
    }
    if (N)
        free(N);
}

void parseMatrix(char const *line, Matrix *m, int row_count)
{
    int i,
        len = strlen(line),
        element,
        start = 0,
        end = 0;
    for (i = 0 ; i < m->C ; i ++)
    {
        char *N = malloc(5);
        while (1)
        {
            end ++;
            if (line[end] == ' ' || line[end] == '\r' || line[end] == '\n')
            {
                strncpy(N, start + line, end - start);
                sscanf(N, "%d", &element);
                m->index[row_count][i] = element;
                // printf("%d\n", element);
                start = end + 1;
                free(N);
                break;
            }
        }
    }
}

void multiplyMatrix(Matrix *m1, Matrix *m2, Matrix *result){
    result->R = m1->R;
    result->C = m2->C;

    int row, col;
    for (row = 0 ; row < result->R ; row ++){
        for (col = 0 ; col < result->C ; col ++){
            int i, temp = 0;
            for (i = 0 ; i < m1->C ; i ++){
                temp += m1->index[row][i] * m2->index[i][col];
            }
            result->index[row][col] = temp;
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
            printf("%d", m->index[i][j]);
            if (j != m->C -1 )
                printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: Floating <floating_input>");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen( argv[1],  "r" );
    char *line = NULL;
    size_t len = 0;

    if (fp == NULL)
    {
        printf("File %s not found.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    Matrix m1, m2, result;
    getline(&line, &len, fp);
    // printf("%s", line);

    parseMatrixSize(line, &m1);
    int i;
    for (i = 0 ; i < m1.R ; i ++)
    {
        getline(&line, &len, fp);
        parseMatrix(line, &m1, i);
    }
    // printMatrix(&m1);

    getline(&line, &len, fp);
    parseMatrixSize(line, &m2);
    for (i = 0 ; i < m2.R ; i ++)
    {
        getline(&line, &len, fp);
        parseMatrix(line, &m2, i);
    }
    // printMatrix(&m2);

    if (m1.C != m2.R){
        result.R = 0;
        result.C = 0;
    } else {
        multiplyMatrix(&m1, &m2, &result);
    }
    
    printMatrix(&result);

    fclose(fp);
    if (line)
        free(line);
    return 0;
}