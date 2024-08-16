#include "error.h"
#include "data_mem.h"
#include <stdlib.h>

int allocate(double **dat, int n)
{
    double *tmp = malloc(sizeof(double) * n)
    int rc = OK;
    if (tmp)
        *dat = tmp;
    else
        rc = ERR_MEM;
    return rc;
}

void destroy(double **mat)
{
    if (*mat)
    {
        free(*mat);
        *mat = NULL;
    }
}