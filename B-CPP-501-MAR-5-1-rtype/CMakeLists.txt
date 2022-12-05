cmake_minimum_required(VERSION 3.10)

project(r-type)

add_definitions("-fPIC")
add_definitions("-g3")
add_definitions("-std=c++17")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

IF(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
ELSE()
    message(FATAL_ERROR "build infos not found.")
ENDIF()

set(SERVER
    Server/TCP/src/ConnexionTcp.cpp
    Server/TCP/src/ParserTcp.cpp
    Server/TCP/src/ServerTcp.cpp
    Server/TCP/src/InfoUser.cpp
    Server/TCP/src/Room.cpp
    Server/UDP/src/ServerUDP.cpp
    Server/Game/src/Game.cpp
    Server/Game/src/Thread.cpp
    Server/main.cpp
)

set(SERVER_H
    Server/TCP/include/ConnexionTcp.hpp
    Server/TCP/include/ParserTcp.hpp
    Server/TCP/include/ServerTcp.hpp
    Server/TCP/include/InfoUser.hpp
    Server/TCP/include/Room.hpp
    Server/UDP/include/ServerUDP.hpp
    Server/Game/include/Game.hpp
    Server/Game/include/Thread.hpp
    #Server/DLLoader.hpp
)

set(GAME_ENGINE_COMP
    Server/GameEngine/Components/src/AI.cpp
    Server/GameEngine/Components/src/ComponentError.cpp
    Server/GameEngine/Components/src/Damage.cpp
    Server/GameEngine/Components/src/Life.cpp
    Server/GameEngine/Components/src/Position.cpp
    Server/GameEngine/Components/src/Speed.cpp
    Server/GameEngine/Components/src/Sprite.cpp
)

set(GAME_ENGINE_COMP_H
    Server/GameEngine/Components/include/AI.hpp
    Server/GameEngine/Components/include/ComponentError.hpp
    Server/GameEngine/Components/include/Damage.hpp
    Server/GameEngine/Components/include/Life.hpp
    Server/GameEngine/Components/include/Position.hpp
    Server/GameEngine/Components/include/Rect.hpp
    Server/GameEngine/Components/include/Speed.hpp
    Server/GameEngine/Components/include/Sprite.hpp
)

set(GAME_ENGINE_INTERFACES
    Server/GameEngine/interfaces/IComponents.hpp
    Server/GameEngine/interfaces/IFComponents.hpp
    Server/GameEngine/interfaces/ITComponents.hpp
    Server/GameEngine/interfaces/IDEntities.hpp
    Server/GameEngine/interfaces/IEntities.hpp
    Server/GameEngine/interfaces/IMonster.hpp
    Server/GameEngine/interfaces/IPlayer.hpp
    Server/GameEngine/interfaces/IProjectile.hpp
)

set(CLIENT
    Client/Graphic/src/SFMLgraph.cpp
    Client/Connexion/ClientTcp/src/BoostClientTcp.cpp
    Client/Graphic/main.cpp
    Client/Connexion/UDPgame/src/UdpGame.cpp
)

set(CLIENT_H
    Client/Graphic/include/SFMLgraph.hpp
    Client/Graphic/include/MenuButton.hpp
    Client/Connexion/ClientTcp/include/BoostClientTcp.hpp
    Client/Connexion/Interface/IClientTcp.hpp
    Client/Connexion/UDPgame/include/UdpGame.hpp
)

set(PLAYER_ENTITY
    Server/GameEngine/Entities/src/Player.cpp
    Server/GameEngine/Entities/src/PlayerProjectile.cpp
    Server/GameEngine/Entities/include/Player.hpp
    Server/GameEngine/Entities/include/PlayerProjectile.hpp
)

set(GAME_ENGINE_ENTITIES
    Server/GameEngine/Entities/src/BasicProjectile.cpp
    Server/GameEngine/Entities/src/FirstMob.cpp
)

set(GAME_ENGINE_ENTITIES_H
    Server/GameEngine/Entities/include/BasicProjectile.hpp
    Server/GameEngine/Entities/include/FirstMob.hpp
)

add_custom_target(destroy DEPENDS destroy_c)    
add_custom_command(OUTPUT destroy_c
    COMMAND rm -rf r-type_client_autogen r-type_server_autogen build CMakeFiles
    COMMAND rm r-type_client r-type_server CMakeCache.txt cmake_install.cmake
)

add_custom_target(autodestroy DEPENDS autodest)    
add_custom_command(OUTPUT autodest
    COMMAND rm -rf r-type_client_autogen r-type_server_autogen build CMakeFiles
)

#add_library(firstmob SHARED
#    ${GAME_ENGINE_ENTITIES}
#    ${GAME_ENGINE_ENTITIES_H}
#    ${GAME_ENGINE_COMP}
#    ${GAME_ENGINE_COMP_H}
#    ${GAME_ENGINE_INTERFACES}
#)

add_executable(r-type_server ${GAME_ENGINE_ENTITIES} ${GAME_ENGINE_ENTITIES_H} ${SERVER} ${SERVER_H} ${GAME_ENGINE_COMP} ${GAME_ENGINE_COMP_H} ${GAME_ENGINE_INTERFACES} ${PLAYER_ENTITY})
add_executable(r-type_client ${CLIENT} ${CLIENT_H})

conan_basic_setup(TARGETS)

#target_link_libraries(r-type_server PRIVATE dl)
#target_link_libraries(r-type_server PRIVATE firstmob)
target_link_libraries(r-type_server PRIVATE CONAN_PKG::boost)
target_link_libraries(r-type_client PRIVATE CONAN_PKG::boost)
target_link_libraries(r-type_client PRIVATE CONAN_PKG::sfml)

include_directories(${CMAKE_INCLUDE_PATH})