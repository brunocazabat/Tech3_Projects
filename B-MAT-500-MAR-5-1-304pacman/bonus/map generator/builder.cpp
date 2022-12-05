/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-304pacman-bruno.cazabat
** File description:
** builder
*/

#include "builder.hpp"
#include "generator.hpp"

Builder::Builder(int x_, int y_, DIR d, Generator *g)
{
    x = x_;
    y = y_;
    dir = d;
    gen = g;
    dist = rand() % (gen->get_y_mapsize() / 3) + 1;
    active = true;
}

Builder::~Builder()
{
}

int Builder::get_x()
{
    return x;
}

int Builder::get_y()
{
    return y;
}

void Builder::change_dir()
{
    int r = std::rand() % 2;

    if (r == 0)
        dir = DIR(dir+1);
    else 
        dir = DIR(dir-1);
    dist = rand() % (gen->get_y_mapsize() / 3) + 1;
    check_dist();
}

void Builder::check_dist()
{
    if (dist > 1)
        switch (dir) {
        case N:
            if (y != 0)
                y = y - 1;
            else
                change_dir();
            break;
        case E:
            if (x != gen->get_x_mapsize()-1)
                x = x + 1;
            else
                change_dir();
            break;
        case S:
            if (y != gen->get_y_mapsize()-1)
                y = y + 1;
            else
                change_dir();
            break;
        case W:
            if (x != 0)
                x = x - 1;
            else
                change_dir();
            break;
        default:
            break;
        }
    else
        change_dir();
}

bool Builder::isActive()
{
    return active;
}

void Builder::run()
{
    check_dist();
    if (gen->get_map()[y][x] == '0')
        active = false;
    else
        gen->set_map(y, x, '0');
}
