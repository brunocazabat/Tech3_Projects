/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "include/radiator.hpp"

static void helpmeimdying(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./306radiator n ir jr [i j]" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tn\tsize of the room" << std::endl;
    std::cout << "\t(ir, jr)\tcoordinates of the radiator" << std::endl;
    std::cout << "\t(i, j)\tcoordinates of a point in the room" << std::endl;
}

int main(int ac, char **av)
{
    int n = 0;
    int nPow = 0;
    int jr = 0;
    int ir = 0;
    int i = 0;
    int j = 0;

    if (ac == 2 and strcmp(av[1], "-h") == 0) {
        helpmeimdying();
    } else if (ac == 4) {
        n = std::atoi(av[1]);
        nPow = n * n;
        ir = std::atoi(av[2]);
        jr = std::atoi(av[3]);
        if (!yonigg(ac, av, n, ir, jr))
            return (84);
        comehereyoulilshit(n, nPow, jr, ir, i, j, "A");
    } else if (ac == 6) {
        n = std::atoi(av[1]);
        nPow = n * n;
        ir = std::atoi(av[2]);
        jr = std::atoi(av[3]);
        i = std::atoi(av[4]);
        j = std::atoi(av[5]);
        if (!allah(ac, av, n, ir, jr, i, j))
            return (84);
        comehereyoulilshit(n, nPow, jr, ir, i, j, "B");
    } else
        return (84);
    return (0);
}