#include "error.h"
#include "data_mem.h"
#include "data_io.h"
#include "data_process.h"
#include <stdio.h>
int main(void)
{
    double *data;
    int n;
    int rc = OK;
    if (scanf("%d", &n) != 1)
    {
        rc = ERR_IO;
    }
    else if (n <= 0)
        rc =ERR_RANGE;
    
    if (!rc)
    {
        rc = allocate(&data, n);
    }

    if (!rc)
        rc = input(data, n);
    
    if (!rc && normalization(data, n))
        output(data, n);
    else
        printf("ERROR");
    return rc;
}
