/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-305construction-bruno.cazabat
** File description:
** main
*/

#include "parser.hpp"

void print_usage()
{
    std::cout << "USAGE\n\t./305construction file\n" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile\tfile describing the tasks" << std::endl;
}

void check_args(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Error, use -h for help" << std::endl;
        exit(84);
    }
    std::string str1 = av[1];
    if (str1.compare("-h") == 0 || str1.compare("--help") == 0) {
        print_usage();
        exit(0);
    }
}

int main (int ac, char **av)
{
    check_args(ac, av);
    Parser parser(av[1]);
    parser.officialPrint();
    return (0);
}