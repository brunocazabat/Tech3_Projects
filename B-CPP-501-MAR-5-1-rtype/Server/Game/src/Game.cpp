/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Game
*/

#include "../include/Game.hpp"

Game::Game(int maxPlayer, ServerUdp &servUdp): _servUdp(servUdp), _nbPlayer(0)
{
    std::string newPlayer;
    std::string pos;
    std::pair<int, int> start;

    start.first = 10;
    start.second = 10;
    while (_nbPlayer != maxPlayer) {
        if (!(newPlayer = isNewPlayer()).empty()) {
            _nbPlayer = _nbPlayer + 1;

            _players.push_back(std::make_shared<Player>(newPlayer, start, static_cast<Player::Colors>(_nbPlayer)));
        }
    }
    //loadMonsters();
    _score = 0;
    _servUdp.send("Thread created game start\n");
    pos = "Position,";
    for (size_t j = 0; j < _players.size(); j++) {
        if (j == 0)
            pos = pos + _players.at(j)->getName() + ":" + std::to_string(_players.at(j)->getPos().first) + ":" + std::to_string(_players.at(j)->getPos().second) + ":" + _players.at(j)->getSprite() + ":" + std::to_string(_players.at(j)->getSpriteRect().posx) + ":" + std::to_string(_players.at(j)->getSpriteRect().posy) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizey);
        else
            pos = pos + "," + _players.at(j)->getName() + ":" + std::to_string(_players.at(j)->getPos().first) + ":" + std::to_string(_players.at(j)->getPos().second) + ":" + _players.at(j)->getSprite() + ":" + std::to_string(_players.at(j)->getSpriteRect().posx) + ":" + std::to_string(_players.at(j)->getSpriteRect().posy) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizey);
    }
    pos = pos + ";Score," + std::to_string(_score);
    pos = pos + "\n";
    _servUdp.send(pos);
    run();
}

Game::~Game()
{
}

std::string Game::isNewPlayer()
{
    std::string response;
    std::string name;

    response = _servUdp.read();

    if (response.size() == 0 || response.find("Server;", 0) == std::string::npos) {
        name = response.substr(0, response.find(';', 0));
    }
    return (name);
}

void Game::run()
{
    std::vector<std::pair<int, int>> pos;
    std::string name;
    std::string response;
    std::vector<std::string> input;
    int posInput;

    while (!isFinish()) {
        _inputPlayer = _servUdp.read();
        if (_inputPlayer.find("Server;", 0) == std::string::npos) {
            posInput = _inputPlayer.find(';', 0);
            name = _inputPlayer.find(posInput, _inputPlayer.find(';', posInput + 1) - posInput);
            posInput = _inputPlayer.find(';', posInput + 1);
            for (size_t i = 0; i < _players.size(); i++) {
                if (_players.at(i)->getName() == name) {
                    manageInputs(_players.at(i), _inputPlayer.at(posInput + 1));
                    checkCollision(_players.at(i));
                }
            }
        }
        for (size_t i = 0; i < _players.size(); i++) {
            pos.push_back(_players.at(i)->getPos());
        }
        for (size_t i = 0; i < _entities.size(); i++) {
            _entities.at(i)->updatePlayerPos(pos);
            _entities.at(i)->update();
            if (_entities.at(i)->isOnFire())
                _projectiles.push_back(std::static_pointer_cast<IProjectile>(_entities.at(i)->fire()));
        }
        for (size_t i = 0; i < _playerProjectiles.size(); i++) {
            checkEnnemyCollision(_playerProjectiles.at(i));
        }
        pos.clear();
        if (!isFinish()) {
            response = "Player,";
            for (size_t j = 0; j < _players.size(); j++) {
                if (j == 0)
                    response = response + _players.at(j)->getName() + ":" + std::to_string(_players.at(j)->getPos().first) + ":" + std::to_string(_players.at(j)->getPos().second) + ":" + _players.at(j)->getSprite() + ":" + std::to_string(_players.at(j)->getSpriteRect().posx) + ":" + std::to_string(_players.at(j)->getSpriteRect().posy) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizey);
                else
                    response = response + "," + _players.at(j)->getName() + ":" + std::to_string(_players.at(j)->getPos().first) + ":" + std::to_string(_players.at(j)->getPos().second) + ":" + _players.at(j)->getSprite() + ":" + std::to_string(_players.at(j)->getSpriteRect().posx) + ":" + std::to_string(_players.at(j)->getSpriteRect().posy) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_players.at(j)->getSpriteRect().sizey);
            }
        }
        if (_entities.size() > 0 || _projectiles.size() > 0 || _playerProjectiles.size() > 0) {
            if (!isFinish())
                response = ";Entities,";
            else
                response = "Entities,";
            for (size_t j = 0; j < _entities.size(); j++) {
                if (j == 0)
                    response = response + _entities.at(j)->getName() + ":" + std::to_string(_entities.at(j)->getPos().first) + ":" + std::to_string(_entities.at(j)->getPos().second) + ":" + _entities.at(j)->getSprite() + ":" + std::to_string(_entities.at(j)->getSpriteRect().posx) + ":" + std::to_string(_entities.at(j)->getSpriteRect().posy) + ":" + std::to_string(_entities.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_entities.at(j)->getSpriteRect().sizey);
                else
                    response = response + _entities.at(j)->getName() + ":" + std::to_string(_entities.at(j)->getPos().first) + ":" + std::to_string(_entities.at(j)->getPos().second) + ":" + _entities.at(j)->getSprite() + ":" + std::to_string(_entities.at(j)->getSpriteRect().posx) + ":" + std::to_string(_entities.at(j)->getSpriteRect().posy) + ":" + std::to_string(_entities.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_entities.at(j)->getSpriteRect().sizey);
            }
            for (size_t j = 0; j < _projectiles.size(); j++) {
                if (j == 0)
                    response = response + _projectiles.at(j)->getName() + ":" + std::to_string(_projectiles.at(j)->getPos().first) + ":" + std::to_string(_projectiles.at(j)->getPos().second) + ":" + _projectiles.at(j)->getSprite() + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().posx) + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().posy) + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().sizey);
                else
                    response = response + _projectiles.at(j)->getName() + ":" + std::to_string(_projectiles.at(j)->getPos().first) + ":" + std::to_string(_projectiles.at(j)->getPos().second) + ":" + _projectiles.at(j)->getSprite() + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().posx) + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().posy) + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_projectiles.at(j)->getSpriteRect().sizey);
            }
            for (size_t j = 0; j < _playerProjectiles.size(); j++) {
                if (j == 0)
                    response = response + _playerProjectiles.at(j)->getName() + ":" + std::to_string(_playerProjectiles.at(j)->getPos().first) + ":" + std::to_string(_playerProjectiles.at(j)->getPos().second) + ":" + _playerProjectiles.at(j)->getSprite() + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().posx) + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().posy) + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().sizey);
                else
                    response = response + _playerProjectiles.at(j)->getName() + ":" + std::to_string(_playerProjectiles.at(j)->getPos().first) + ":" + std::to_string(_playerProjectiles.at(j)->getPos().second) + ":" + _playerProjectiles.at(j)->getSprite() + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().posx) + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().posy) + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().sizex) + ":" + std::to_string(_playerProjectiles.at(j)->getSpriteRect().sizey);
            }
        }
        if (!isFinish() || _entities.size() > 0 || _projectiles.size() > 0 || _playerProjectiles.size() > 0)
            response = response + ";Score," + std::to_string(_score);
        else
            response = response + "Score," + std::to_string(_score);
        response = response + "\n";
        _servUdp.send(response);
        spawnEnnemy();
    }
}

void Game::manageInputs(std::shared_ptr<Player> player, char input)
{
    switch (input) {
        case ('z'):{
            if (player.get()->getPos().second <= 10)
                return;
            else
                player.get()->move('y', -10);
        }
        case ('s'):{
            if (player.get()->getPos().second >= 1070)
                return;
            else
                player.get()->move('y', 10);
        }
        case ('d'):{
            if (player.get()->getPos().first >= 1910)
                return;
            else
                player.get()->move('x', 10);
        }
        case ('q'):{
            if (player.get()->getPos().first <= 10)
                return;
            else
                player.get()->move('x', -10);
        }
        case (' '):{
            if (player.get()->isOnFire())
                _playerProjectiles.push_back(std::static_pointer_cast<IProjectile>(player.get()->fire()));
        }
    }
}

void Game::checkCollision(std::shared_ptr<Player> player)
{
    int posx = player.get()->getPos().first + player.get()->getSpriteRect().sizex / 2;
    int posy = player.get()->getPos().second + player.get()->getSpriteRect().sizey / 2;

    for (size_t i = 0; i < _entities.size(); i++) {
        if (((posx >= _entities.at(i)->getPos().first) && (posx <= _entities.at(i)->getPos().first + _entities.at(i)->getPos().first)) && ((posy >= _entities.at(i)->getPos().second) && (posy <= _entities.at(i)->getPos().second + _entities.at(i)->getPos().second))) {
            if (!player.get()->hit(50)) {
                for (size_t i = 0; i < _players.size(); i++) {
                    if (_players.at(i) == player) {
                        _players.erase(_players.begin() + i);
                        return;
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < _projectiles.size(); i++) {
        if (((posx >= _projectiles.at(i)->getPos().first) && (posx <= _projectiles.at(i)->getPos().first + _projectiles.at(i)->getSpriteRect().sizex)) && ((posy >= _projectiles.at(i)->getPos().second) && (posy <= _projectiles.at(i)->getPos().second + _projectiles.at(i)->getSpriteRect().sizey))) {
            if (!player.get()->hit(_projectiles.at(i)->getDamage())) {
                for (size_t i = 0; i < _players.size(); i++) {
                    if (_players.at(i) == player) {
                        _players.erase(_players.begin() + i);
                        return;
                    }
                }
            }
            _projectiles.erase(_projectiles.begin() + i);
        }
    }
}

void Game::checkEnnemyCollision(std::shared_ptr<IProjectile> proj)
{
    int posx;
    int posy;

    for (size_t i = 0; i < _entities.size(); i++) {
        posx = _entities.at(i).get()->getPos().first + _entities.at(i).get()->getSpriteRect().sizex / 2;
        posy = _entities.at(i).get()->getPos().second + _entities.at(i).get()->getSpriteRect().sizey / 2;
        if (((posx >= proj->getPos().first) && (posx <= proj->getPos().first + proj->getSpriteRect().sizex)) && ((posy >= proj->getPos().second) && (posy <= proj->getPos().second + proj->getSpriteRect().sizey))) {
            if (!_entities.at(i).get()->hit(proj->getDamage())) {
                _entities.erase(_entities.begin() + i);
            }
            for (size_t i = 0; i < _playerProjectiles.size(); i++) {
                if (_playerProjectiles.at(i) == proj) {
                    _playerProjectiles.erase(_playerProjectiles.begin() + i);
                    return;
                }
            }
        }
    }
    for (size_t i = 0; i < _projectiles.size(); i++) {
        posx = _projectiles.at(i).get()->getPos().first + _projectiles.at(i).get()->getSpriteRect().sizex / 2;
        posy = _projectiles.at(i).get()->getPos().second + _projectiles.at(i).get()->getSpriteRect().sizey / 2;
        if (((posx >= proj->getPos().first) && (posx <= proj->getPos().first + proj->getSpriteRect().sizex)) && ((posy >= proj->getPos().second) && (posy <= proj->getPos().second + proj->getSpriteRect().sizey))) {
            if (!_projectiles.at(i).get()->canBeHit()) {
                _projectiles.erase(_projectiles.begin() + i);
                for (size_t i = 0; i < _playerProjectiles.size(); i++) {
                    if (_playerProjectiles.at(i) == proj) {
                        _playerProjectiles.erase(_playerProjectiles.begin() + i);
                        return;
                    }
                }
            }
        }
    }
}

bool Game::isFinish()
{
    if (_players.size() > 0)
        return (false);
    return (true);
}

void Game::spawnEnnemy()
{
    static int id = 0;
    //DLLoader<IDEntities> load;
    //void *handler;
    int nb = rand() % _monstersList.size();
    id = id + 1;

    //IMonster *mob = dynamic_cast<IMonster *>(load.getInstance(_monstersList.at(nb), &handler));
    std::shared_ptr<FirstMob> mob = std::make_shared<FirstMob>(FirstMob());
    mob->setPos(1920, rand() % 800 + 100);
    mob->setName(std::to_string(id));
    this->_entities.push_back(std::static_pointer_cast<IMonster>(mob));
    //this->_entitiesHandler->push_back(handler);
}

bool Game::loadMonsters()
{
    DIR *dir = opendir("./");
    struct dirent *sd;
    std::string tmp;

    if (dir == NULL)
        return (false);
    _monstersList.clear();
    while ((sd = readdir(dir)) != NULL) {
        tmp = std::string(sd->d_name);
        if ((tmp.size() > 3 && tmp.substr(tmp.size() - 3, tmp.size()) == ".so" && PLATFORM == LINUX) || (tmp.size() > 4 && tmp.substr(tmp.size() - 4, tmp.size()) == ".dll" && PLATFORM == WINDOWS)) {
            
            _monstersList.push_back("./" + std::string(sd->d_name));
        }
    }
    return (true);
}