##
## EPITECH PROJECT, 2021
## gomoku
## File description:
## Makefile
##

SRC 		=	src/AI.py

BIN_NAME 	= 	pbrain-gomoku-ai

all:
	cp ${SRC} ${BIN_NAME}
	chmod +x ${BIN_NAME}

# pyinstaller --noconfirm --onefile --console --name "pbrain-ai"  "F:/Documents/Epitech/B-AIA-500-MAR-5-1-gomoku-samuel.parayre/src/AI.py"

clean: fclean

fclean:
	rm ${BIN_NAME}

re: fclean all

.PHONY: all clean fclean re