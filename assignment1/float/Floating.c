#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

union float_bits
{
    float f;
    unsigned int bits;
};

struct human_float
{
    int sign;
    int exponent;
    int mantissa;
};

// print hex( 5.Of ) outputs "The float looks like Ox4OaOOOOO in hex."
void print_hex( float f)
{
    union float_bits t;
    t.f = f;
    printf( "The float looks like Ox%x in hex.\n", t.bits );
}

void print_human_float ( float f )
{
    union float_bits t;
    t.f = f;
    unsigned int float_hex = t.bits;

    struct human_float hf;
    hf.sign = (t.bits >> 31) & 0x1;
    hf.exponent = ((t.bits >> 23) & 0xFF) - 127;
    hf.mantissa = t.bits & 0x7FFFFF;

    char sign_char[3];
    if (hf.exponent == -126)
    {
        if (hf.sign == 1)
            strcpy(sign_char, "-0");
        else
            strcpy(sign_char, "0");
    }
    else
    {
        if (hf.sign == 1)
            strcpy(sign_char, "-1");
        else
            strcpy(sign_char, "1");
    }
    char *mantissa_char = malloc(sizeof(char) * (24));
    if (mantissa_char == NULL)
    {
        printf("Malloc failed.\n");
        exit(1);
    }
    int i;
    for (i = 0; i < 23; ++i)
    {
        char ch = (char)(((int)'0') + ((hf.mantissa >> (22 - i)) & 0x1));
        mantissa_char[i] = ch;
    }
    mantissa_char[23] = '\0';
    printf("%s.%s * 2^%d\n", sign_char, mantissa_char, hf.exponent);
    free(mantissa_char);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: Floating <floating_input>");
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    float f;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("File %s not found.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    int n;
    getline(&line, &len, fp);
    sscanf(line, "%d", &n);
    while (n-- > 0)
    {
        getline(&line, &len, fp);
        sscanf(line, "%f", &f);
        print_human_float(f);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

    return 0;
}