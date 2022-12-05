/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

typedef std::vector<float>      Line;
typedef std::vector<Line>       Matrix;
typedef std::pair<int, int>     Point;

void    print_usage(char **av);
bool    is_number(const std::string& s);
Point   getPivotIndex(Matrix M);
Matrix  createMatrix(Line N, Line P);
Matrix  applyPivot(Matrix M, int y_p, int x_p);
std::pair<Line, Matrix>     simplexe(Matrix M);

namespace bruh {
    class multi
    {
    public:
        float n1;
        float n2;
        float n3;
        float n4;
        float f1;
        float f2;
        float f3;
        float f4;
        float f5;

        multi();
        ~multi();
    };
}