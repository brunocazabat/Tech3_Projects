/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "00include.hpp"

dannon::bruh::bruh() {}
dannon::bruh::~bruh() {}

int     dannon::bruh::numb_check(const char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (isdigit(str[i]) || str[i] == '-' || str[i] == '+' || str[i] == '.') {
            i++;
        } else {
            return (84);
        }
    }
    return (0);
}

void     dannon::bruh::help(char *program) {
    
    std::cerr << "USAGE\n\t" << program << " file" << std::endl;
    std::cerr << "DESCRIPTION\n\tfile\tfile that contains the numbers to be sorted, separeted by spaces" << std::endl;
}

void    dannon::bruh::output() {
    
    if (this->list.size() == 1)
        std::cout << this->list.size()        << " element"      << std::endl;
    if (this->list.size() != 1)
        std::cout << this->list.size()        << " elements"      << std::endl;
    std::cout << "Selection sort: " << selection(this->list)  << " comparisons" << std::endl;
    std::cout << "Insertion sort: " << insertion(this->list)  << " comparisons" << std::endl;
    std::cout << "Bubble sort: "    << bubbles(this->list)    << " comparisons" << std::endl;
    std::cout << "Quicksort: "      << quick(this->list)      << " comparisons" << std::endl;
    std::cout << "Merge sort: "     << fusion(this->list)      << " comparisons" << std::endl;
}

int     main(int ac, char **av) {
    
    dannon::bruh b;

    b.ifStream.open(av[1]);
    if (ac != 2 || strcmp(av[1],"-h") == 0) {
        b.help(av[0]);
        return (84);
    }
    if (!b.ifStream) {
        std::cerr << av[1] << " IS AN UNREADABLE FILE." << std::endl;
        return (84);
    }
    std::getline(b.ifStream, b.line);
    std::istringstream iStringStream(b.line);
    while (std::getline(iStringStream, b.word, ' ')) {
        if (b.numb_check(b.word.c_str()) == 0) {
            b.list.push_back(std::atof(b.word.c_str()));
        } else {
            std::cerr << "THE FILE IS CORRUPTED OR CONTAIN INVALID CARACTERS." << std::endl;
            return (84);
        }
    }
    if (!b.list.size()) {
        std::cerr << av[1] << " IS AN EMPTY FILE." << std::endl;
        return (84);
    }
    b.output();
    return (0);
}