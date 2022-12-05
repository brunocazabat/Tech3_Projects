/*
** EPITECH PROJECT, 2021
** 309pollution
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include "parser.hpp"

void print_usage()
{
    std::cout << "USAGE\n\t./309pollution n file x y\n" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tn\tnumber of points on the grid axis" << std::endl;
    std::cout << "\tfile\tcsv file containing the data points x;y;p" << std::endl;
    std::cout << "\tx\tabscissa of the point whose pollution level we want to know" << std::endl;
    std::cout << "\ty\tordinate of the point whose pollution level we want to know" << std::endl;
}

void check_args(int ac, char **av)
{
    if (ac == 2) {
        std::string str1 = av[1];
        if (str1.compare("-h") == 0 || str1.compare("--help") == 0) {
            print_usage();
            exit(0);
        }
    }
    if (ac != 5) {
        std::cout << "Error, use -h for help" << std::endl;
        exit(84);
    }
}

int main (int ac, char **av)
{
    check_args(ac, av);
    Parser parser(av);
    parser.printResults();
    return (0);
}