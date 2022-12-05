/*
** EPITECH PROJECT, 2020
** B-CPP-501-MAR-5-1-rtype-guillaume.corbet
** File description:
** Strings for client
*/

#ifndef STRS_HPP_
#define STRS_HPP_

#define WINDOW_NAME     "R-TYPE"
#define ENTER_NAME      "NAME: "
#define ENTER_IP        "SERVER IP: "
#define ENTER_PORT      "PORT: "
#define ENTER_CODE      "CODE: "
#define DEFAULT_USER    "User"
#define DEFAULT_IP      "127.0.0.1"
#define DEFAULT_PORT    "8080"
#define DEFAULT_CODE    "ABCDE"
#define PLAY            "PLAY"
#define CONNECT         "CONNECT"
#define JOIN            "JOIN"
#define CREATE          "CREATE"
#define QUIT            "QUIT"
#define START_GAME      "START"

#define LINUX 0
#define WINDOWS 1

#ifdef __linux__
    #define MENU_FONT_PATH  "Fonts/neuropolitical rg.ttf"
    #define MENU_BG_PATH    "Wallpapers/rtype_menu_wp.jpg"
    #define WR_BG_PATH      "Wallpapers/rtype_wr_wp.jpg"
    #define PLATFORM LINUX
#elif defined _WIN32 || defined _WIN64
    #define MENU_FONT_PATH  "../../../Fonts/neuropolitical rg.ttf"
    #define MENU_BG_PATH    "../../../Wallpapers/rtype_menu_wp.jpg"
    #define WR_BG_PATH      "../../../Wallpapers/rtype_wr_wp.jpg"
    #define PLATFORM WINDOWS
#else
    #error "unknown error"
#endif


#define ROOM_JOINED     "100\n"
#define ROOM_CREATED    "101"
#define LEAVE_ROOM      "102\n"
#define EXIT            "103\n"
#define LOGIN_SUCCESS   "104\n"
#define NAMES_RETURNED  "105\n"
#define GAME_STARTED    "Start";

#define NOT_LOGIN       "500\n"
#define LOGIN_ERROR     "501\n"
#define ALREADY_IN_ROOM "502\n"
#define ROOM_FULL       "503\n"
#define ERROR_CODE_ROOM "504\n"
#define NO_ROOM         "505\n"
#define NOT_IN_ROOM     "506\n"

#define SUCCESS         0
#define ERROR           84

#endif /* !STRS_HPP_ */
