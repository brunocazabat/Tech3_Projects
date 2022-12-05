/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#include "include/allah.hpp"

void    print_usage(char **av)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t" << av[0] << " n1 n2 n3 n4 po pw pc pb ps" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tn1\tnumber of tons of fertilizer F1" << std::endl;
    std::cout << "\tn2\tnumber of tons of fertilizer F2" << std::endl;
    std::cout << "\tn3\tnumber of tons of fertilizer F3" << std::endl;
    std::cout << "\tn4\tnumber of tons of fertilizer F4" << std::endl;
    std::cout << "\tpo\tprice of one unit of oat" << std::endl;
    std::cout << "\tpw\tprice of one unit of wheat" << std::endl;
    std::cout << "\tpc\tprice of one unit of corn" << std::endl;
    std::cout << "\tpb\tprice of one unit of barley" << std::endl;
    std::cout << "\tps\tprice of one unit of soy" << std::endl;
}