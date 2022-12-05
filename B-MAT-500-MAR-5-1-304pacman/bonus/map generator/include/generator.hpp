/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-304pacman-bruno.cazabat
** File description:
** generator
*/

#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "builder.hpp"

class Generator
{
    public:
        Generator(char*, char*);
        ~Generator();
        int get_x_mapsize();
        int get_y_mapsize();
        std::vector<std::vector<char>> get_map();
        void set_map(int y, int x, char c);
        void run();
        void create_basic_map();
        void assign_spawners();
        void create_spawners();
        void create_builders(int x, int y);
        void replace_s();
        int run_builders();
        void add_characters();
        bool check_row_sp(int ry);
        bool check_col_sp(int rx);
        void write_map(std::string filename);
        void print_map();

    private:
        int x_mapsize;
        int y_mapsize;
        std::vector<std::vector<char>> vect_map;
        std::vector<Builder> vect_builders;
};

#endif /* !GENERATOR_HPP_ */
