/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

bruh::reedpipe::reedpipe() {}
bruh::reedpipe::~reedpipe() {}

int main(int ac, char **av)
{
    bruh::reedpipe b;

    std::string line;
    try {
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            print_usage(av);
            return (0);
        }
        if (ac != 7 || !b.checkSyntaxInt(av[6]))
            return (84);
        for (int i = 1; i < 6; i++)
            if (!b.checkSyntaxDouble(av[i]))
                return (84);
        try {
            b.var["r0"] = std::atof(av[1]);
            b.var["r5"] = std::atof(av[2]);
            b.var["r10"] = std::atof(av[3]);
            b.var["r15"] = std::atof(av[4]);
            b.var["r20"] = std::atof(av[5]);
            b.var["n"] = std::atoi(av[6]);
        } catch (...) {
            return (84);
        }
        if (b.var["n"] <= 0 || b.var["r0"] <= 0 || b.var["r5"] <= 0 || b.var["r10"] <= 0 || b.var["r15"] <= 0 || b.var["r20"] <= 0)
            return (84);
        if (b.var["r0"] != b.var["n"])
            b.ordinate.push_back(b.var["r0"]);
        if (b.var["r5"] != b.var["n"])
            b.ordinate.push_back(b.var["r5"]);
        if (b.var["r10"] != b.var["n"])
            b.ordinate.push_back(b.var["r10"]);
        if (b.var["r15"] != b.var["n"])
            b.ordinate.push_back(b.var["r15"]);
        if (b.var["r20"] != b.var["n"])
            b.ordinate.push_back(b.var["r20"]);
        b.compute();
        printf("vector result: [");
        for (int i = 0; i < b.vect.size(); i++) {
            if ((b.vect[i] > 0 && b.vect[i] < 0.1) || (b.vect[i] > -0.1 && b.vect[i] < 0))
                printf("0.0");
            else
                printf("%.1f", b.vect[i]);
            if (i + 1 < b.vect.size())
                printf(", ");
        }
        printf("]\n");
        for (int i = 0; i < b.var["n"]; i++) {
            printf("abscissa: %.1f cm\tradius: %.1f cm\n", 20 / (b.var["n"] - 1) * i, b.res[i]);
        }
    } catch (...) { return (84); }
    return (0);
}