##
## EPITECH PROJECT, 2020
## ouioui
## File description:
## oui
##

NAME	= 302separation

CC	= g++

RM	= rm -f

SRCS	= ./src/addfunc.cpp \
	  ./src/main.cpp \
	  ./src/print_func.cpp \
	  ./src/sortandparser.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/include/
CPPFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)
	 $(RM) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
