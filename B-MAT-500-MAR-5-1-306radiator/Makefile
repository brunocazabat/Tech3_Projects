##
## EPITECH PROJECT, 2020
## ouioui
## File description:
## oui
##

NAME	= 306radiator

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/1projet.cpp \
	  ./src/2de.cpp \
	  ./src/3merde.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./include/pp
CPPFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
