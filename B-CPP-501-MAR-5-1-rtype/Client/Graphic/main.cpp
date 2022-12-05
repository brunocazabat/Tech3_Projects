/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** main
*/

#include "include/SFMLgraph.hpp"
#include <iostream>

int main(int ac, char **av)
{
    SFMLgraph *client = new SFMLgraph();
    int value = 0;

    while (client->isWindowOpened()) {
        if (value != client->Game) {
            client->getMenuEvents();
            client->checkMouseMenu();
            value = client->getGameState();
            if (value == client->WaitingRoom) {
                client->displayNames();
            }
        } else {
            client->getGameEvents();
        }
        client->display();
    }
    return SUCCESS;
}
