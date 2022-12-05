/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Player
*/

#include "../include/Player.hpp"

Player::Player(std::string name, std::pair<int, int> pos, Player::Colors color)
{
    _name = name;
    _canFire = true;
    _count = 0;
    _components.push_back(std::make_shared<Life>(200));
    _components.push_back(std::make_shared<Position>(pos));
    _components.push_back(std::make_shared<Speed>(std::pair<int, int>(0, 0)));
    _components.push_back(std::make_shared<Sprite>(SPRITES_PATH + "r-typesheet42.gif;0;" + std::to_string(color * 17) + ";33;17;5"));
}

Player::~Player()
{
}

void Player::move(char axis, int value)
{
    if (axis == 'X' || axis == 'x') {
        std::static_pointer_cast<Position>(getComponent(IElem::Position))->updateBySpeed(std::pair<int, int>(value, 0));
    } else if (axis == 'y' || axis == 'Y') {
        std::static_pointer_cast<Position>(getComponent(IElem::Position))->updateBySpeed(std::pair<int, int>(0, value));
    }
}

void Player::update()
{
    if (!_canFire)
        _count++;
    if (_count >= 10) {
        _count = 0;
        _canFire = true;
    }
    (*std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))) += 1;
}

void Player::display()
{

}

bool Player::hit(int nb)
{
    (*std::static_pointer_cast<Life>(getComponent(IElem::Life))) -= nb;
    if (std::static_pointer_cast<Life>(getComponent(IElem::Life))->get() <= 0) {
        return (false);
    }
    return (true);
}

std::pair<int, int> Player::getPos()
{
    return (std::static_pointer_cast<Position>(getComponent(IElem::Position))->get());
}

std::string Player::getSprite()
{
    return (std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->get());
}

Rect Player::getSpriteRect()
{
    std::pair<int, int> pos = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectPos();
    std::pair<int, int> size = std::static_pointer_cast<Sprite>(getComponent(IElem::Sprite))->getRectSize();

    return (Rect(pos.first, pos.second, size.first, size.second));
}

bool Player::isOnFire()
{
    return (_canFire);
}

std::shared_ptr<IDEntities> Player::fire()
{
    _canFire = false;
    return (std::make_shared<PlayerProjectile>(getPos(), PlayerProjectile::TYPES::Classic));
}