/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#include "include/allah.hpp"

bruh::multi::multi() {}
bruh::multi::~multi() {}

int     main(int ac, char **av)
{
    bruh::multi b;

    std::string line;
    try {
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            print_usage(av);
            return (0);
        }
        if (ac != 10) {
            std::cerr << "Bad usage." << std::endl;
            return (84);
        }
    } catch (...) { return (84); }
    try {
        for (int i = 1; i < 10; i++)
            if (!is_number(std::string(av[i]))) {
                std::cerr << "Invalid syntax." << std::endl;
                return (84);
            }
        b.n1 = std::atoi(av[1]);
        b.n2 = std::atoi(av[2]);
        b.n3 = std::atoi(av[3]);
        b.n4 = std::atoi(av[4]);
        b.f1 = std::atoi(av[5]);
        b.f2 = std::atoi(av[6]);
        b.f3 = std::atoi(av[7]);
        b.f4 = std::atoi(av[8]);
        b.f5 = std::atoi(av[9]);
        if (b.n1 < 0 || b.n2 < 0 || b.n3 < 0 || b.n4 < 0 ||
            b.f1 < 0 || b.f2 < 0 || b.f3 < 0 || b.f4 < 0 || b.f5 < 0) {
            std::cerr << "Invalid Usage. Can't be negative number." << std::endl;
            return (84);
        }
        Line N = { b.n1, b.n2, b.n3, b.n4 };
        Line P = { b.f1, b.f2, b.f3, b.f4, b.f5 };
        Matrix M = createMatrix(N, P);
        std::pair<Line, Matrix> res2 = simplexe(M);
        Line res = res2.first;
        M = res2.second;
        std::vector<float> dump = { 0, 0, 0, 0, 0 };
        float tt = 0;

        for (int i = 0; i < 4; i++)
            if (res[i] != -1) {
                if (M[i][M[i].size() - 1] != 0) {
                    dump[res[i]] = M[i][M[i].size() - 1];
                    tt += M[i][M[i].size() - 1] * P[res[i]];
                } else
                    dump[res[i]] = M[i][M[i].size() - 1];
            }
        printf("Resources: %.0f F1, %.0f F2, %.0f F3, %.0f F4\n\n", b.n1, b.n2, b.n3, b.n4);
        if (dump[0] == 0)
            printf("Oat: 0 units at $%.0f/unit\n", b.f1);
        else
            printf("Oat: %.2f units at $%.0f/unit\n", dump[0], b.f1);
        if (dump[1] == 0)
            printf("Wheat: 0 units at $%.0f/unit\n", b.f2);
        else
            printf("Wheat: %.2f units at $%.0f/unit\n", dump[1], b.f2);
        if (dump[2] == 0)
            printf("Corn: 0 units at $%.0f/unit\n", b.f3);
        else
            printf("Corn: %.2f units at $%.0f/unit\n", dump[2], b.f3);
        if (dump[3] == 0)
            printf("Barley: 0 units at $%.0f/unit\n", b.f4);
        else
            printf("Barley: %.2f units at $%.0f/unit\n", dump[3], b.f4);
        if (dump[4] == 0)
            printf("Soy: 0 units at $%.0f/unit\n\n", b.f5);
        else
            printf("Soy: %.2f units at $%.0f/unit\n\n", dump[4], b.f5);
        printf("Total production value: $%.2f", tt);
    } catch (...) { return (84); }
    return (0);
}