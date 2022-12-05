##
## EPITECH PROJECT, 2020
## ouioui
## File description:
## oui
##

NAME	= generator

CC	= g++

RM	= rm -f

SRCS	= 	generator.cpp  		\
			builder.cpp		\
			main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./include/
CPPFLAGS += -Wall -Wextra -g

all: $(NAME)

all2:$(NAME2)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)
	 $(RM) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re