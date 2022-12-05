#!/usr/bin/python
import os
import sys

#--------------------------------------------------------------
# Globals
#--------------------------------------------------------------

PERMANENTFOLDER = ""
BOARDFILE = "./board.txt"
BOARD = []
BOARDSIZE = []
SIZE = 20
BOARDSCORE = [[]]

#--------------------------------------------------------------
# String Functions
#--------------------------------------------------------------

def get_line():
    	return sys.stdin.readline()


def output(string):
    print(string)
    sys.stdout.flush()


def is_composed(str1, chars):
    for letter in str1:
        if letter not in chars:
            return False
    return True


def is_int(cmd):
    for character in cmd:
        if character not in "0123456789":
            return False
    return True

#--------------------------------------------------------------
# Board Manipulations
#--------------------------------------------------------------

def get_board_state():
    global PERMANENTFOLDER
    global BOARDFILE
    global BOARD
    if not os.path.isfile(PERMANENTFOLDER + BOARDFILE):
        return ("no_file")
    get_board()
    if BOARD is None:
        return ("empty_file")
    lines = len(BOARD)
    size = len(BOARD[0])
    for elm in BOARD:
        if len(elm) != size or not is_composed(elm, "012"):
            return ("invalid_file")
    return ("{},{}".format(size, lines))


def check_board_state():
    if get_board_state() != "20,20":
        return False
    return True


def get_board():
    global BOARD
    with open(PERMANENTFOLDER + BOARDFILE, 'r') as myfile:
        tab = myfile.read()
        BOARD = tab.split('\n')


def create_empty_board(x, y):
    global BOARD
    BOARD = []
    line = ""
    for i in range(0, x):
        line += "0"
    for i in range(0, y):
        BOARD.append(line)


def save_board():
    global PERMANENTFOLDER
    global BOARDFILE
    global BOARD
    with open(PERMANENTFOLDER + BOARDFILE, 'w') as myfile:
        for elm in BOARD:
            myfile.write(elm + "\n")


def modify_board(x, y, playerchar):
    global BOARD
    BOARD[y] = BOARD[y][:x] + playerchar + BOARD[y][x + 1:]


def play(x, y):
    modify_board(x, y, '1')


def ennemy_play(x, y):
    modify_board(x, y, '2')

#--------------------------------------------------------------
# AI core
#--------------------------------------------------------------

def set_direction(dir):
    if dir == 0:
        return (-4, 0, 1, 0)
    elif dir == 1:
        return (-4, -4, 1, 1)
    elif dir == 2:
        return (0, -4, 0, 1)
    elif dir == 3:
        return (-4, 4, 1, -1)
    return (0, 0, 0, 0)


def count_dir(dir, x, y, player):
    global BOARD
    global SIZE
    global BOARDSIZE
    stone_align = 0
    max_align = 0
    empty_place = 0
    score = 0
    stop_count_align = False
    vector_x, vector_y, inc_x, inc_y = set_direction(dir)

    ally_weights = [0, 20, 150, 400, 80000]
    ennemy_weights = [0, 18, 140, 360, 6000]

    for i in range (9):
        if x + vector_x >= 0 and x + vector_x < SIZE:
            if y + vector_y >= 0 and y + vector_y < SIZE:
                if BOARD[y + vector_y][x + vector_x] == '0':
                    stone_align += 1
                    if i < 4:
                        max_align = 0
                        empty_place = 1
                    elif i > 4:
                        if not stop_count_align:
                            empty_place += 1
                        if stone_align > 4:
                            if max_align > 4:
                                max_align = 4
                            if player == '1':
                                score += ally_weights[max_align]
                            elif player == '2':
                                score += ennemy_weights[max_align]
                        max_align = 0
                        stop_count_align = True
                elif BOARD[y + vector_y][x + vector_x] == player:
                    stone_align += 1
                    #score += 1
                    if not stop_count_align:
                        max_align += 1
                    if i == 8:
                        if max_align > 4:
                            max_align = 4
                        if player == '1' and stone_align > 4:
                            score += ally_weights[max_align]
                        elif player == '2' and stone_align > 4:
                            score += ennemy_weights[max_align]
                        max_align = 0
                else:
                    if i < 4:
                        max_align = 0
                        empty_place = 0
                    elif i > 4:
                        if max_align > 4:
                            max_align = 4
                        if player == '1' and stone_align > 4:
                            score += ally_weights[max_align]
                        elif player == '2' and stone_align > 4:
                            score += ennemy_weights[max_align]
                        max_align = 0
                        stop_count_align = True
                    stone_align = 0
                if stone_align > 4:
                    score += 1
        x += inc_x
        y += inc_y
    if max_align != 0:
        if player == '1':
            score += ally_weights[max_align]
        elif player == '2':
            score += ennemy_weights[max_align]
    if empty_place == 2:
        score = score * 2
    return score


def is_adjacent(x, y):
    global BOARD
    global SIZE

    if BOARD[y][x] != '0':
        return False
    if x >= 1 and x < SIZE - 1 and y >= 1 and y < SIZE - 1:
        if BOARD[y][x - 1] != '0' or BOARD[y][x + 1] != '0' or BOARD[y - 1][x] != '0' or BOARD[y + 1][x] != '0' or BOARD[y - 1][x - 1] != '0' or BOARD[y - 1][x + 1] != '0' or BOARD[y + 1][x - 1] != '0' or BOARD[y + 1][x + 1] != '0':
            return True
    if x == 0:
        if BOARD[y][x + 1] != '0':
            return True
        if y >= 1 and (BOARD[y - 1][x + 1] != '0' or BOARD[y - 1][x] != '0'):
            return True
        if y < SIZE - 1 and (BOARD[y + 1][x + 1] != '0' or BOARD[y + 1][x] != '0'):
            return True
    elif x == SIZE - 1:
        if BOARD[y][x - 1] != '0':
            return True
        if y >= 1 and (BOARD[y - 1][x - 1] != '0' or BOARD[y - 1][x] != '0'):
            return True
        if y < SIZE - 1 and (BOARD[y + 1][x - 1] != '0' or BOARD[y + 1][x] != '0'):
            return True
    if y == 0:
        if BOARD[y + 1][x] != '0':
            return True
        if x >= 1 and (BOARD[y + 1][x - 1] != '0' or BOARD[y + 1][x] != '0'):
            return True
        if x < SIZE - 1 and (BOARD[y + 1][x - 1] != '0' or BOARD[y + 1][x] != '0'):
            return True
    elif y == SIZE - 1:
        if BOARD[y - 1][x] != '0':
            return True
        if x >= 1 and (BOARD[y - 1][x - 1] != '0' or BOARD[y - 1][x] != '0'):
            return True
        if x < SIZE - 1 and (BOARD[y - 1][x + 1] != '0' or BOARD[y - 1][x] != '0'):
            return True
    return False


def find_tile(player):
    global BOARD
    global SIZE
    global BOARDSCORE

    temp = []
    BOARDSCORE.clear()
    for j in range(20):
        temp.append(0)
    for i in range (20):
        BOARDSCORE.append(temp.copy())
    max_score = 0
    tile_x, tile_y = -1,-1
    score = 0
    for y in range(0, SIZE):
        for x in range(0, SIZE):
            if is_adjacent(x, y):
                for i in range(4):
                    score += count_dir(i, x, y, player)
                    score += count_dir(i, x, y, '2')
                #print("x = {}, y = {}, score = {}".format(x, y, score))
                BOARDSCORE[y][x] = score
                if score > max_score:
                    max_score = score
                    tile_x = x
                    tile_y = y
                score = 0
    with open("./boardscore", 'w') as myfile:
        for line in BOARDSCORE:
            for elm in line:
                myfile.write(str(elm) + ";")
            myfile.write("\n")
    return tile_x, tile_y

#--------------------------------------------------------------
# Communication
#--------------------------------------------------------------

def start_cmd(cmd):
    command = cmd.split(' ')
    if len(command) > 1:
        strin = command[1].rstrip("\r\n")
    else:
        output("ERROR - Wrong number of arguments or wrong argument type")
        return
    if len(command) > 1 and strin.isdigit() and int(strin) != 20:
        output("ERROR - unsupported size")
    elif (len(command) > 1 and not strin.isdigit()):
        output("ERROR - Wrong number of arguments or wrong argument type")
    else:
        create_empty_board(int(strin), int(strin))
        output("OK")


def turn_cmd(cmd):
    tmp = cmd.split(' ')
    tmp = tmp[1].split(',')

    if len(tmp) == 2:
        x = tmp[0]
        y = tmp[1].rstrip("\r\n")

    if len(tmp) != 2:
        output("ERROR - unsupported size")
    elif not is_int(x) or not is_int(y):
        output("ERROR - wrong argument type")
    else:
        ennemy_play(int(x), int(y))
        x, y = find_tile('1')
        output("{},{}".format(x, y))
        play(x, y)


def begin_cmd(cmd):
    command = cmd.split(' ')
    if len(command) > 1:
        output("Error - Wrong number of arguments")
    else:
        output("10,10")
        play(10, 10)


def board_cmd(cmd):
    test = False
    temp = cmd.split('\n')
    tmp = cmd

    while temp[0] != "DONE":
        temp = get_line()
        tmp = "".join((tmp, temp))
        temp = temp.split('\n')
    tmp = tmp.split('\n')
    failure = 0
    for elm in tmp:
        elm.strip("\r\n")
        if elm == "BOARD":
            continue
        if elm == "DONE":
            break
        test = True
        line = elm.split(',')
        if len(line) != 3:
            output("ERROR - wrong line")
            failure = 1
        elif not is_int(line[0]) or not is_int(line[1]) or (line[2] != "1" and line[2] != "2"):
            output("ERROR - wrong argument in line")
            failure = 1
    if not failure:
        create_empty_board(20, 20)
        if not test:
            output("10,10")
            play(10, 10)
            return
        for elm in tmp:
            elm.strip("\r\n")
            if elm == "BOARD":
                continue
            if elm == "DONE":
                break
            line = elm.split(',')
            modify_board(int(line[0]), int(line[1]), line[2])
        x, y = find_tile('1')
        output("{},{}".format(x, y))
        play(x, y)


def info_cmd(cmd):
    #command = cmd.split(" ")
    """
    if len(cmd) < 3:
        return
    key = {
        "timeout_turn" : timeout_turn_key,
        "timeout_match" : timeout_match_key,
        "max_memory" : max_memory_key,
        "time_left" : time_left_key,
        "game_type" : game_type_key,
        "rule" : rule_key,
        "evaluate" : evaluate_key,
        "folder" : folder_key
    }
    if command[0] in key:
        key[command[0]](command[2])
    """


def end_cmd(cmd):
    save_board()
    exit(0)


def about_cmd(cmd):
    command = cmd.split(' ')
    if len(command) > 1 :
        return
    output("name=\"{}\", version=\"{}\", author=\"{}\", country=\"FR\"".format("MMBrain", "1.0", "CCGang"))


def restart_cmd(cmd):
    global SIZE
    command = cmd.split(' ')
    if len(command) > 1 :
        output("ERROR - unsupported argument")
        return
    create_empty_board(SIZE, SIZE)
    output("OK")


def ai(cmd):
    args_list = {
        "START": start_cmd,
        "TURN": turn_cmd,
        "BEGIN": begin_cmd,
        "BOARD": board_cmd,
        "INFO": info_cmd,
        "END": end_cmd,
        "ABOUT": about_cmd,
        "RESTART": restart_cmd
    }
    params = cmd.split(' ')
    com = params[0].rstrip("\r\n")
    if com in args_list:
        args_list[com](cmd)
    else :
        output("UNKNOWN - Unknown command : {}".format(cmd))

#--------------------------------------------------------------
# Main
#--------------------------------------------------------------

if __name__ == "__main__":
    # get_board()
    # tab = find_tile('1')
    # for elm in tab:
    #     print(elm)
    temp = []

    for i in range (20):
        temp.append(0)
    for j in range(20):
        BOARDSCORE.append(temp.copy())

    while True:
        cmd = get_line()
        ai(cmd)