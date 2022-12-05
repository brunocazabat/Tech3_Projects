##
## EPITECH PROJECT, 2020
## B-MAT-500-MAR-5-1-305construction-bruno.cazabat
## File description:
## Makefile
##

NAME	= 305construction

CC	= g++

RM	= rm -f

SRCS	= 	src/main.cpp	\
			src/parser.cpp	\
			src/task.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./include/
CPPFLAGS += -Wall -Wextra -g

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