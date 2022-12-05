/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** BasicProjectile
*/

#include "../include/BasicProjectile.hpp"

BasicProjectile::BasicProjectile(std::pair<int, int> pos, int damages)
{
    _components.push_back(std::make_shared<Position>(pos));
    _components.push_back(std::make_shared<Damage>(damages));
    _components.push_back(std::make_shared<Speed>(std::pair<int, int>(-20, 0)));
    _components.push_back(std::make_shared<Sprite>(SPRITES_PATH + "r-typesheet1.gif;267;170;81;16;2"));
}

BasicProjectile::~BasicProjectile()
{
}

void BasicProjectile::update()
{
    std::static_pointer_cast<Position>(getComponent(IElem::Position))->updateBySpeed(std::static_pointer_cast<Speed>(getComponent(IElem::Speed))->get());
}

void BasicProjectile::display()
{

}

bool BasicProjectile::hit(int nb)
{
    return (true);
}

int BasicProjectile::getDamage()
{
    return (std::static_pointer_cast<Damage>(getComponent(IElem::Damage))->get());
}

std::pair<int, int> BasicProjectile::getPos()
{
    return (std::static_pointer_cast<Position>(getComponent(IElem::Position))->get());
}

std::string BasicProjectile::getSprite()
{
    return (std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->get());
}

Rect BasicProjectile::getSpriteRect()
{
    std::pair<int, int> pos = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectPos();
    std::pair<int, int> size = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectSize();

    return (Rect(pos.first, pos.second, size.first, size.second));
}