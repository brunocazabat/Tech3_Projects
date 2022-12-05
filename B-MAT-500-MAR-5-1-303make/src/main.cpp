/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include "include/include.hpp"

int     main(int ac, char **av)
{
    make::bruh b;
    std::vector<std::string>    wordTab;

    if (b.error_handler(ac, av, 1) != 1)
	    return (b.retval);

    else if (ac >= 2 && ac <= 3)
    {
        wordTab = b.getWordTabFromFile(av[1]);
        if (wordTab.empty())
            return (84);
        b.dataparser(wordTab);
        if (ac == 2)
            b.compile(b.getmapper(), b.getmapper2(), "");
        else
            b.compile(b.getmapper(), b.getmapper2(), av[2]);
    }
    else
        return (b.error_handler(ac, av, 2));
    return 0;
}