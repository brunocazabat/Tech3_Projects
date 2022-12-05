/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include "include/include.hpp"

separation::bruh::bruh() {}
separation::bruh::~bruh() {}

int     main(int ac, char **av)
{
    separation::bruh b;
    b.delim = (" is friends with ");

    if (b.error_handler(ac, av, 1) != 1)
        return (b.retval);
    std::ifstream infile(av[1]);
    while (std::getline(infile, b.line))
        b.listnameparser();
    std::sort(b.names.begin(), b.names.end(), std::greater<std::string>());
    b.firstnamesort();
    if (ac == 3 && b.validNb(av[2]))
        b.dualnamesort();
    else if (ac == 4 && b.comp_twonames(av) == 0)
        return (0);
    else
        return(b.error_handler(ac, av, 2));

    return (0);
}