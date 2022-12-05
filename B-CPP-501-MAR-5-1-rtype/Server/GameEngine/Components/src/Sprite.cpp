/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Sprite
*/

#include "../include/Sprite.hpp"

Sprite::Sprite(std::string path)
{
    std::string tmp = path.substr(path.find(';') + 1);
    _value = path.substr(0, path.find(';'));

    for (size_t i = 0; i < 4; i++) {
        if (!tmp.empty()) {
            switch (i) {
                case (0):
                    _rectPos.first = (std::stoi(tmp.substr(0, tmp.find(';'))));
                case (1):
                    _rectPos.second = (std::stoi(tmp.substr(0, tmp.find(';'))));
                case (2):
                    _rectSize.first = (std::stoi(tmp.substr(0, tmp.find(';'))));
                case (3):
                    _rectSize.second = (std::stoi(tmp.substr(0, tmp.find(';'))));
            }
            tmp = tmp.substr(tmp.find(';') + 1);
        }
    }
}

Sprite::~Sprite()
{
}

std::pair<int, int> Sprite::getRectPos() const
{
    return (_rectPos);
}

std::pair<int, int> Sprite::getRectSize() const
{
    return (_rectSize);
}

void Sprite::setRectPos(int x, int y)
{
    if (x != -1)
        _rectPos.first = x;
    if (y != -1)
        _rectPos.second = y;
}

void Sprite::setRectSize(int x, int y)
{
    if (x != -1)
        _rectSize.first = x;
    if (y != -1)
        _rectSize.second = y;
}

void Sprite::operator+=(int nb)
{
    _rectPos.first += nb * _rectSize.first;
    if (_rectPos.first >= _maxAnim * _rectSize.first)
        _rectPos.first = 0;
}

void Sprite::operator-=(int nb)
{
    _rectPos.first -= nb * _rectSize.first;
    if (_rectPos.first <= 0)
        _rectPos.first = (_maxAnim - 1) * _rectSize.first;
}