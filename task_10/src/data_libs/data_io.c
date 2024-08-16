#include "data_io.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

int input(double *data, int n)
{
    int rc = OK;
    for (int i = 0; !rc && i < n; i++)
    {
        if (scanf("%lf", &data[i]) != 1)
        {
            rc = ERR_IO;
        }
    }
    return rc;
}
void output(double *data, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("%.6lf ", data[i]);
    }
    printf("%.6lf", data[n - 1]);
}
