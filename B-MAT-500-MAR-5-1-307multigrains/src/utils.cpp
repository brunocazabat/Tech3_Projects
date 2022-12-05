/*
** EPITECH PROJECT, 2021
** ouioui
** File description:
** oui
*/

#include "include/allah.hpp"

Point getPivotIndex(Matrix M)
{
    size_t  max_y = M.size();
    if (max_y <= 0)
        return Point(-1, -1);
    size_t  max_x = M[0].size();
    if (max_x <= 5)
        return Point(-1, -1);
    Line    line = M[max_y - 1];
    Line    copyL;
    for (int i = 0; i < 5; i++) {
        copyL.push_back(line[i]);
    }
    float minV = 99999999999999;

    for(float i : copyL) {
        minV = std::min(i, minV);
    }
    if (minV >= 0)
        return Point(-1, -1);
    int     xPivot = -1, yPivot = -1;

    xPivot = std::distance(copyL.begin(), std::find(copyL.begin(), copyL.end(), minV));
    minV = 99999999999999;
    for (int i = 0; i < max_y - 1; i++)
    {
        if (M[i][max_x - 1])
        {
            if (M[i][xPivot] > 0 &&
                (minV > M[i][max_x - 1] / M[i][xPivot] &&
                M[i][max_x - 1] / M[i][xPivot] > 0))
            {

                yPivot = i;
                minV = M[i][max_x - 1] / M[i][xPivot];
            }
        }
        else if (minV > M[i][xPivot] && M[i][xPivot] > 0)
        {
                yPivot = i;
                minV = M[i][max_x - 1] / M[i][xPivot];
        }
    }
    return (Point(yPivot, xPivot));
}

bool    is_number(const std::string& s)
{
    for (int i = 0; i < s.size(); i++)
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (false);
    return (true);
}

Matrix createMatrix(Line N, Line P)
{
    Line minusP;
    for (int value : P)
        minusP.push_back(-value);
    for (int i = 0; i < 5; i++)
        minusP.push_back(0);
    Matrix M = {
        Line { 1, 0, 1, 0, 2 },
        Line { 1, 2, 0, 1, 0 },
        Line { 2, 1, 0, 1, 0 },
        Line { 0, 0, 3, 1, 2 },
        minusP
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == i)
                M[i].push_back(1);
            else
                M[i].push_back(0);
        }
        M[i].push_back(N[i]);
    }
    return (M);
}

Matrix applyPivot(Matrix M, int y_p, int x_p)
{
    float p_value = M[y_p][x_p];
    for (int i = 0; i < M[y_p].size(); i++) {
        M[y_p][i] = M[y_p][i] / p_value;
    }
    int maxy = M.size();
    int maxx = M[0].size();
    for (int i = 0; i < maxy; i++) {
        if (i == y_p)
            continue;
        float km = M[i][x_p];
        for (int j = 0; j < maxx; j++)
            M[i][j] -= km * M[y_p][j];
    }
    return (M);
}

std::pair<Line, Matrix> simplexe(Matrix M)
{
    Line products;
    for (int i = 0; i < 4; i++)
        products.push_back(-1);
    int i = 0;
    while (true)
    {
        i++;
        if (i == 6)
            break;
        Point p = getPivotIndex(M);
        int x_p = p.second;
        int y_p = p.first;
        if (y_p < 0 || x_p < 0)
            break;
        M = applyPivot(M, y_p, x_p);
        products[y_p] = x_p;
    }
    return std::pair<Line, Matrix>(products, M);
}