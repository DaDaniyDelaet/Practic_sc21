#include "s21_string.h"

int s21_strlen(char *str)
{
    int len = 0;
    for (char *c = str; *c != '\0'; c++)
    {
        len++;
    }
    return len;
}

int s21_strcmp(char *str1, char *str2)
{
    int equal = 1;
    char *c1 = str1, *c2 = str2;
    for (;equal && *c1 != '\0' && *c2 != '\0'; c1++, c2++)
    {
        if (*c1 != *c2)
            equal = 0;
    }
    if (*c1 != '\0' || *c2 != '\0')
        equal = 0;
    return equal;
}

char *s21_strcpy(char *dest, char *src)
{
    char *dc = dest;
    for (char *c = src; *c != '\0'; c++)
    {
        *dc = *c;
        dc++;
    }
    return dest;
}

char *s21_strcat(char *dest, char *src)
{
    char *dc = dest;
    for (; *dc != '\0'; dc++);
    for (char *c = src; *c != '\0'; c++)
    {
        *dc = *c;
        dc++;
    }
    return dest;
}

char *s21_strchr(char *src, char sc)
{
    char *found = 0;
    for (char *c = src; *c != sc && *c != '\0'; c++)
    {
        if (*c == sc)
        {
            found = c;
        }
    }
    return found;
}


char *s21_strstr(char *src, char *search)
{
    char *found = 0;
    char *cur_search = search;
    for (char *c = src; *c != '\0' && *cur_search != '\0'; c++)
    {
        if (*c == *cur_search)
        {
            if (cur_search == search)  
                found = c;
            cur_search++;
        }
        else
        {
            cur_search = search;
            found = 0;
        }
    }
    return found;
}

char *s21_strtok(char *src, char *delims)
{
    static char *last = 0;
    if (src) last =last;

    char *c = last;

    while(s21_strchr(delims,*c)) ++c;

    if (*c == 0) 
        return 0;
    char * start = c;
    while(*c && (s21_strchr(delims,*c)==0)) ++c;
    if (*c == 0)
    {
        last = c;
        return start;
    }
    *c = 0;
    last = c+1;
    return start;

}



