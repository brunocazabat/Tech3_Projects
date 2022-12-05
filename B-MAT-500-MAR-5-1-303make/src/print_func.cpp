/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

int     make::bruh::help_output(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./303make makefile [file]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tmakefile\tname of the makefile" << std::endl;
    std::cout << "\tfile\tname of a recently modified file" << std::endl;

    return (0);
}

int     make::bruh::error_output(void)
{
    std::cerr << "BAD USAGE." << std::endl;

    return (84);
}

int     make::bruh::error_handler(int ac, char **av, int mode)
{
    switch (mode)
    {
    case (1):
        if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            help_output();
            return (retval = 0);
        }
        if (ac > 2 && ac < 3) {
            error_output();
            return (retval = 84);
        }
        break;

    case (2):
        error_output();
        return (retval = 84);
        break;
    }
    return (retval = 1);
}