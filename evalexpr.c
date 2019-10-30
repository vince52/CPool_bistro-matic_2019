/*
** EPITECH PROJECT, 2019
** CPool_bistro-matic_2019
** File description:
** No file there, just an epitech header example
*/
#include"include/my.h"
#include "include/my_inf_add.h"
#include<unistd.h>
#include<stdlib.h>

char *inf_mult(char *nb1, char *nb2, char const *base);
char *inf_mod(char *a, char *b, char *base);
char *inf_div(char *a, char *b, char *base);
char *modifstr(char *str);

char  *my_strtol(char **str)
{
    char *str_num = malloc(sizeof(char)*my_strlen(str[0]));
    int i = 0;
    int j = 0;
    for (; (str[0][i] < 48 || str[0][i] > 57) && str[0][i] != 0; i++);
    for (; str[0][i] != 0 && str[0][i] >= 48 && str[0][i] <= 57; i++, j++)
        str_num[j] = str[0][i];
    str[0] = &str[0][i];
    return str_num;
}

char *remove_par(char **s, int i)
{
    char *str = *s;
    int par = 0;
    int x = i + 1;
    for (; str[x] != ')' || par != 0; x++){
        if (str[x] == '(')
            par += 1;
        if (str[x] == ')')
            par -= 1;
    }
    char *str1 = malloc(sizeof(char) * x - 1 - i);
    for (int j = 0; j < my_strlen(str1); j++)
        str1[j] = 0;
    my_strncpy(str1, str + i + 1, x - 1 - i);
    *s = &str[x - 1];
    return str1;
}

char *eval_expr(char const *s, char *spec);

char *operation(char **str, int i, int verifzero)
{
    char *s = *str;
    char *res;
    if (s[i + 1] == '(')
        res = eval_expr(remove_par(str, 1));
    else
        res = my_strtol(str);
    if (verifzero && res == 0) {
        write(2, "Cannot divide or modulo by zero\n", 32);
        return NULL;
    }
    else
        return res;
}

char *eval_expr(char const *s, char *spec)
{
    char *str = my_strdup(s);
    char *res = my_strtol(&str);
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == spec[2])
            res = inf_add(res, operation(&str, i, 0));
        if (str[i] == spec[3])
            res = inf_sub(res, operation(&str, i, 0));
        if (str[i] == spec[4])
            res = inf_mult(res, operation(&str, i, 0), NULL);
        if (str[i] == spec[5])
            res = inf_div(res, operation(&str, i, 0), "0123456789");
        if (str[i] == spec[6])
            res = inf_mod(res, operation(&str, i, 0), "0123456789");
        if (str[i] != spec[2] && str[i] != spec[3] &&
            str[i] != spec[4] && str[i] != spec[5] && str[i] != spec[6])
            str = str + 1;
    }
    return res;
}