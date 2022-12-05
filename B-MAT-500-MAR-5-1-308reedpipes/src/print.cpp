/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

void    print_usage(char **av)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t" << av[0] << " r0 r5 r10 r15 r20 n" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tr0\tradius (in cm) of pipe at the 0cm abscissa" << std::endl;
    std::cout << "\tr5\tradius (in cm) of pipe at the 5cm abscissa" << std::endl;
    std::cout << "\tr10\tradius (in cm) of pipe at the 10cm abscissa" << std::endl;
    std::cout << "\tr15\tradius (in cm) of pipe at the 15cm abscissa" << std::endl;
    std::cout << "\tr20\tradius (in cm) of pipe at the 20cm abscissa" << std::endl;
    std::cout << "\tn\tnumber of points needed to display the radius" << std::endl;
}