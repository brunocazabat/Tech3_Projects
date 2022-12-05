/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-304pacman-bruno.cazabat
** File description:
** builder
*/

#ifndef BUILDER_HPP_
#define BUILDER_HPP_

#include <cstdlib>

class Generator;

class Builder
{
    public:
        enum DIR {N, E, S, W};
        Builder(int x, int y, DIR d, Generator *g);
        ~Builder();
        int get_x();
        int get_y();
        Generator getGenerator();
        bool isActive();
        void check_dist();
        void change_dir();
        void run();

    private:
        Generator *gen;
        int x;
        int y;
        DIR dir;
        int dist;
        bool active;
};

#endif /* !BUILDER_HPP_ */
