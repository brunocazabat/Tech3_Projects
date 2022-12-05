/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

bool bruh::reedpipe::checkSyntaxInt(char *av)
{
    for (int i = 0; av[i]; i++)
        if (av[i] < '0' || av[i] > '9')
            return (false);
    return (true);
}

bool bruh::reedpipe::checkSyntaxDouble(char *av)
{
    for (int i = 0; av[i]; i++)
        if (av[i] != '.' && (av[i] < '0' || av[i] > '9'))
            return (false);
    return (true);
}

void bruh::reedpipe::compute()
{
    float A, B, C;

    A = 6 * (var["r10"] - 2 * var["r5"] + var["r0"]) / 50;
    B = 6 * (var["r15"] - 2 * var["r10"] + var["r5"]) / 50;
    C = 6 * (var["r20"] - 2 * var["r15"] + var["r10"]) / 50;
    vect[2] = (B - (A + C) / 4) * 4 / 7;
    vect[1] = A / 2 - 0.25 * vect[2];
    vect[3] = C / 2 - 0.25 * vect[2];

    for(int d = 1; d < var["n"]; d++)
    {
        float x = 20 / (var["n"] * d);
        float   i = (int)((x - 0.01) / 5) + 1;
        float result = (- vect[i - 1] / 30 * pow(x - abscissa[i], 3) \
                      + vect[i] / 30 * pow(x - abscissa[i - 1], 3)
                      - (ordinate[i - 1] / 5 - 5 / 6 * vect[i - 1])
                      * (x - abscissa[i])
                      + (ordinate[i] / 5 - 5 / 6 * vect[i])
                      * (x - abscissa[i - 1]));
        res.push_back(result);
    }
}