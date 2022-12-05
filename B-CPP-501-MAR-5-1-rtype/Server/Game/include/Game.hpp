/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#define LINUX 0
#define WINDOWS 1

#ifdef __linux__
    #define MONSTERS_PATH "Monsters/"
    #define PLATFORM LINUX
#elif defined _WIN32 || defined _WIN64
    #define MONSTERS_PATH "../../../Monsters/"
    #define PLATFORM WINDOWS
#else
    #error "unknown platform"
#endif

#include <dirent.h>
#include <dlfcn.h>
#include "../../UDP/include/ServerUDP.hpp"
#include "../../GameEngine/Entities/include/Player.hpp"
#include "../../GameEngine/Entities/include/FirstMob.hpp"
#include "../../GameEngine/interfaces/IMonster.hpp"
//#include "../../DLLoader.hpp"

class Game {
    public:
        Game(int maxPlayer, ServerUdp &servUdp);
        ~Game();
        std::string isNewPlayer();
        void manageInputs(std::shared_ptr<Player> player, char input);
        void checkCollision(std::shared_ptr<Player> player);
        void checkEnnemyCollision(std::shared_ptr<IProjectile> proj);
        void run();
        bool isFinish();
        void spawnEnnemy();
        bool loadMonsters();

    protected:
    private:
        std::vector<std::shared_ptr<Player>> _players;
        std::vector<std::shared_ptr<IProjectile>> _playerProjectiles;
        std::vector<std::shared_ptr<IMonster>> _entities;
        std::vector<std::shared_ptr<IProjectile>> _projectiles;
        std::vector<std::string> _monstersList;
        std::vector<void *> *_entitiesHandler;
        int _score;
        int _nbPlayer;
        std::string _inputPlayer;
        ServerUdp &_servUdp;
};

#endif /* !GAME_HPP_ */
