/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** PlayerProjectile
*/

#include "../include/PlayerProjectile.hpp"

PlayerProjectile::PlayerProjectile(std::pair<int, int> pos, PlayerProjectile::TYPES type)
{
    _components.push_back(std::make_shared<Position>(pos));
    _components.push_back(std::make_shared<Damage>(50));
    _components.push_back(std::make_shared<Speed>(std::pair<int, int>(30, 0)));
    _components.push_back(std::make_shared<Sprite>(SPRITES_PATH + "r-typesheet2.gif;267;170;81;16;2"));
}

PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::update()
{
    std::static_pointer_cast<Position>(getComponent(IElem::Position))->updateBySpeed(std::static_pointer_cast<Speed>(getComponent(IElem::Speed))->get());
}

void PlayerProjectile::display()
{

}

bool PlayerProjectile::hit(int nb)
{
    return (true);
}

int PlayerProjectile::getDamage()
{
    return (std::static_pointer_cast<Damage>(getComponent(IElem::Damage))->get());
}

std::pair<int, int> PlayerProjectile::getPos()
{
    return (std::static_pointer_cast<Position>(getComponent(IElem::Position))->get());
}

std::string PlayerProjectile::getSprite()
{
    return (std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->get());
}

Rect PlayerProjectile::getSpriteRect()
{
    std::pair<int, int> pos = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectPos();
    std::pair<int, int> size = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectSize();

    return (Rect(pos.first, pos.second, size.first, size.second));
}