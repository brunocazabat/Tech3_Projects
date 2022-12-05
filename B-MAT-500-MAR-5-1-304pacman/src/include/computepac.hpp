/*
** EPITECH PROJECT, 2020
** ouioui
** File description:
** oui
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <tuple>

namespace bruh {
    class computepac
    {
    public:
        int 									xf;
	    int 									yf;
        std::vector<std::vector<int>>   		_map;
	    std::vector<std::tuple<int, int, int>>	_tuple;
	    bool 									_found = false;
        
        computepac(const std::vector<std::string> &wordTab);
        ~computepac();

        void        MapPrinter(char c1, char c2);
	    void 		compute();
        bool        dijkstraWayFinder(int x, int y, int current_prof, int max_prof);
	    void 	    ghostfinder();
        void        initBasMap(const std::vector<std::string> &wordTab);
    };
}