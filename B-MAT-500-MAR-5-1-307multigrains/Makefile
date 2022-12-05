##
## EPITECH PROJECT, 2021
## ouioui
## File description:
## oui
##

NAME	= 307multigrains

CC	= g++

RM	= rm -f

SRCS	= ./src/main.cpp \
	  ./src/print.cpp \
	  ./src/utils.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/include/pp
CPPFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
