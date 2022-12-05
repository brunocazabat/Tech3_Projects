/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#include "include/computepac.hpp"

void        bruh::computepac::MapPrinter(char c1, char c2)
{
    for (const std::vector<int> &line: _map)
    {
        for (const int &nb: line)
        {
            if (nb == -1)
                std::cout << c2;
            else if (nb == -2)
                std::cout << c1;
            else if (nb == -3)
                std::cout << 'P';
            else if (nb == -4)
                std::cout << 'F';
            else
                std::cout << nb % 10;
        }
        std::cout << std::endl;
    }
}

void 		bruh::computepac::compute()
{
	this->ghostfinder();

	std::tuple<int, int, int> first(this->xf, this->yf, 0);
	this->_tuple.push_back(first);
	for (unsigned int i = 0; i < (_map.size() * _map[0].size()); i++)
	{
		std::vector<std::tuple<int, int, int>>	save(_tuple);
		for (auto thisTuple: save)
			if (dijkstraWayFinder(std::get<0>(thisTuple), std::get<1>(thisTuple), std::get<2>(thisTuple), i))
				break;
		if (_found)
			break;
	}
	if (!_found)
		exit(84);
}

bool        bruh::computepac::dijkstraWayFinder(int x, int y, int current_prof, int max_prof)
{
	if (y >= (int)_map.size() || x >= (int)_map[y].size() || _map[y][x] == -2 || _map[y][x] >= 0 || _found)
		return (false);
	if (current_prof > max_prof)
	{
		std::tuple<int, int, int> new_tuple(x, y, current_prof);
		_tuple.push_back(new_tuple);
		return (false);
	}
	if (_map[y][x] == -1)
		_map[y][x] = current_prof;
	else if (_map[y][x] == -3)
	{
		_found = true;
		return (true);
	}
	if (dijkstraWayFinder(x, y - 1, current_prof + 1, max_prof))
		return (true);
	if (dijkstraWayFinder(x + 1, y, current_prof + 1, max_prof))
		return (true);
	if (dijkstraWayFinder(x, y + 1, current_prof + 1, max_prof))
		return (true);
	if (dijkstraWayFinder(x - 1, y, current_prof + 1, max_prof))
		return (true);
	return (false);
}

void 	bruh::computepac::ghostfinder()
{
	for (int y = 0; y < (int)_map.size(); y++)
	{
		for (int x = 0; x < (int)_map[y].size(); x++)
		{
			if (_map[y][x] == -4)
			{
				this->xf = x;
				this->yf = y;
				return ;
			}
		}
	}
}

void    bruh::computepac::initBasMap(const std::vector<std::string> &wordTab)
{
    std::vector<int>    line;

    for (const std::string &lineTab: wordTab)
    {
        for (const char c: lineTab)
        {
            if (c == '0')
                line.push_back(-1);
            else if (c == '1')
                line.push_back(-2);
            else if (c == 'P')
                line.push_back(-3);
            else if (c == 'F')
                line.push_back(-4);
        }
        _map.push_back(line);
        line.clear();
    }
}