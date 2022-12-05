##
## EPITECH PROJECT, 2021
## 309pollution
## File description:
## Makefile
##


NAME	= 309pollution

CC	= g++

RM	= rm -f

SRCS	= 	src/main.cpp	\
			src/parser.cpp

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