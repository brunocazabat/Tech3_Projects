/*
** EPITECH PROJECT, 2020
** B-MAT-500-MAR-5-1-304pacman-bruno.cazabat
** File description:
** generator
*/

#include "generator.hpp"

Generator::Generator(char *x, char*y)
{
    x_mapsize = atoi(x);
    y_mapsize = atoi(y);
}

Generator::~Generator()
{
}

int Generator::get_x_mapsize()
{
    return x_mapsize;
}

int Generator::get_y_mapsize()
{
    return y_mapsize;
}

std::vector<std::vector<char>> Generator::get_map()
{
    return vect_map;
}

void Generator::set_map(int y, int x, char c)
{
    vect_map[y][x] = c;
}


void Generator::create_basic_map()
{
    if (x_mapsize < 6 || y_mapsize < 6) {
        std::cout << "please specify a bigger map size : x and y must be at least 6 to avoid errors" << std::endl;
        exit(84);
    }
    std::vector<std::vector<char>> vec(y_mapsize, std::vector<char> (x_mapsize, '1'));
    vect_map = vec;
}

void Generator::print_map()
{
    for (int i = 0; i < y_mapsize; i++) {
        for(int j = 0; j < x_mapsize; j++) {
            std::cout << vect_map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Generator::write_map(std::string filename)
{
    std::ofstream os(filename);

    if (os) {
        for (int i = 0; i < y_mapsize; i++) {
            for(int j = 0; j < x_mapsize; j++) {
                os << vect_map[i][j];
            }
            os << std::endl;
        }
    }
}

bool Generator::check_row_sp(int ry)
{
    for (int i = 0; i < x_mapsize; i++) {
        if (vect_map[ry][i] == 'S')
            return true;
    }
    return false;
}

bool Generator::check_col_sp(int rx)
{
    for (int i = 0; i < y_mapsize; i++) {
        if (vect_map[i][rx] == 'S')
            return true;
    }
    return false;
}

int Generator::run_builders()
{
    int j = 0;
    for(size_t i = 0; i < vect_builders.size(); i++) {
        if (vect_builders[i].isActive()) {
            vect_builders[i].run();
            j++;
        }
    }
    return j;
}

void Generator::create_builders(int x, int y)
{
    int nb_builder = (rand() % 2) + 2;

    std::vector<int> dir_seq = {0, 1, 2, 3};
    std::random_shuffle(dir_seq.begin(), dir_seq.end());

    for (int i = 0; i < nb_builder; i++) {
        switch (dir_seq[i]) {
        case 0:
            if (y != 0) {
                Builder builder = Builder(x, y-1, Builder::N, this);
                vect_map[builder.get_y()][builder.get_x()] = '0';//B
                vect_builders.push_back(builder);
            }
            break;
        case 1:
            if (x != x_mapsize-1) {
                Builder builder = Builder(x+1, y, Builder::E, this);
                vect_map[builder.get_y()][builder.get_x()] = '0';//B
                vect_builders.push_back(builder);
            }
            break;
        case 2:
            if (y != y_mapsize-1) {
                Builder builder = Builder(x, y+1, Builder::S, this);
                vect_map[builder.get_y()][builder.get_x()] = '0';//B
                vect_builders.push_back(builder);
            }
            break;
        case 3:
            if (x != 0) {
                Builder builder = Builder(x-1, y, Builder::W, this);
                vect_map[builder.get_y()][builder.get_x()] = '0';//B
                vect_builders.push_back(builder);
            }
            break;
        default:
            break;
        }
    }
}

void Generator::assign_spawners()
{
    int rx;
    int ry;

    while(1) {
        ry = rand() % y_mapsize;
        if (check_row_sp(ry) == false)
            break;
    }
    while(1) {
        rx = rand() % x_mapsize;
        if (check_col_sp(rx) == false)
            break;
    }
    vect_map[ry][rx] = 'S';
    create_builders(rx, ry);
}

void Generator::create_spawners()
{
    int nb_spawners;

    if (x_mapsize < y_mapsize)
        nb_spawners = x_mapsize * 2 / 3;
    else
        nb_spawners = y_mapsize * 2 / 3;
    for (int i = nb_spawners; i != 0; i--) {
        assign_spawners();
    }
}

void Generator::replace_s()
{
    for (int i = 0; i < y_mapsize; i++) {
        for(int j = 0; j < x_mapsize; j++) {
            if (vect_map[i][j] == 'S')
                vect_map[i][j] = '0';
        }
    }
}

void Generator::add_characters()
{
    int ry;
    int rx;
 
    while(1) {
        ry = rand() % y_mapsize;
        rx = rand() % x_mapsize;
        if (vect_map[ry][rx] == '0') {
            vect_map[ry][rx] = 'F';
            break;
        }
    }
    while(1) {
        ry = rand() % y_mapsize;
        rx = rand() % x_mapsize;
        if (vect_map[ry][rx] == '0') {
            vect_map[ry][rx] = 'P';
            break;
        }
    }        
}

void Generator::run()
{
    create_basic_map();
    create_spawners();
    replace_s();
    while (run_builders() != 0);
    add_characters();
}