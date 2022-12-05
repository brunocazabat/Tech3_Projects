/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-304pacman-bruno.cazabat
** File description:
** main
*/

#include "generator.hpp"

void print_usage()
{
    std::cout << "Utilisation : ./generator x y filename [OPTION]" << std::endl;
    std::cout << "Génère une map 2D de Pacman, où, 1 correspond à un mur et 0 à un chemin." << std::endl << std::endl;
    std::cout << "  -d\taffiche la map généré sur le terminal" << std::endl;
}

bool isNumber(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if (std::isdigit(str[i]) == false)
            return false;
    return true;
}

void check_args(int ac, char **av)
{
    std::string str1 = av[1];
    if (str1.compare("-h") == 0 || str1.compare("--help") == 0) {
        print_usage();
        exit(0);
    }
    if (ac < 4) {
        print_usage();
        exit(84);
    }
    if(isNumber(av[1]) == false || isNumber(av[2]) == false) {
        print_usage();
        exit(84);
    }
}

void check_args2(int ac, char **av, Generator generator)
{
    if (ac == 5) {
        std::string str4 = av[4];
        if (str4.compare("-d") == 0)
            generator.print_map();
    }
}

int main(int ac, char **av)
{
    check_args(ac, av);
    Generator generator(av[1], av[2]);

    std::srand(time(NULL));
    generator.run();
    generator.write_map(av[3]);
    check_args2(ac, av, generator);
}