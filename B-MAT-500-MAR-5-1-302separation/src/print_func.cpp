/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/include.hpp"

int     separation::bruh::help_output(char **av)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t" << av[0] << " file [n | p1 p2]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile\tfile that contains the list of Facebook connections" << std::endl;
    std::cout << "\tn\tmaximum length of the paths" << std::endl;
    std::cout << "\tpi\tname of someone in the file" << std::endl;

    return (0);
}

int     separation::bruh::error_output(void)
{
    std::cerr << "BAD USAGE." << std::endl;

    return (84);
}

int     separation::bruh::final_output(char **av, int to_string, int mode)
{
    if (mode == 1)
        std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": " << std::to_string(to_string) << std::endl;
    if (mode == 2)
        std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": -1" << std::endl;

    return (0);
}

int     separation::bruh::error_handler(int ac, char **av, int mode)
{
    switch (mode)
    {
    case (1):
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            help_output(av);
            return (retval = 0);
        }
        if (ac != 3 && ac != 4) {
            error_output();
            return (retval = 84);
        }
        break;

    case (2):
        error_output();
        return (retval = 84);
        break;
    }
    return (1);
}