##
## EPITECH PROJECT, 2020
## ouioui
## File description:
## oui
##

NAME	= 301dannon

CC	= g++

RM	= rm -f

SRCS	= ./src/bubble.cpp \
	  ./src/insertion.cpp \
	  ./src/main.cpp \
	  ./src/merge.cpp \
	  ./src/quick.cpp \
	  ./src/selection.cpp 

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
