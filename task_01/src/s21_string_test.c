#include "s21_string.h"
#include <stdio.h>
#define OK 0
#define ERR_FAILED_TEST 1

int s21_strcmp_test()
{
    printf("__STRCMP__\n");
    int rc = OK;
    printf("TEST 1: ");
    if (!s21_strcmp("", ""))
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 2: ");
    if (!s21_strcmp("1234567890","1234567890" ))
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 3: ");
    if (!s21_strcmp("\t\n\r\a", "\t\n\r\a"))
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 4: ");
    if (s21_strcmp("", "d"))
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 5: ");
    if (s21_strcmp("1234567890","1234567a890" ))
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 6: ");
    if (s21_strcmp("\t\n\r\a", "\n\r\a"))
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");
    return rc;
}

int s21_strlen_test()
{
    int rc = OK;
    printf("TEST 1: ");
    if (s21_strlen("") != 0)
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 2: ");
    if (s21_strlen("1234567890") != 10)
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");

    printf("TEST 3: ");
    if (s21_strlen("\t\n\r\a") != 4)
    {
        printf("FAILED\n");
        rc = ERR_FAILED_TEST;
    }
    else
        printf("SUCCESS\n");
    return rc;
}

int main(void)
{
    s21_strlen_test();
    s21_strcmp_test();
}