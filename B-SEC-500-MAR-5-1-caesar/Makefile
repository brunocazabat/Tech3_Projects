
##
## EPITECH PROJECT, 2020
## Delivery
## File description:
## Makefile
##

NAME1    = challenge01
NAME2    = challenge02
NAME3    = challenge03
NAME4    = challenge04
NAME5    = challenge05
NAME6    = challenge06
NAME7	 = challenge07
NAME8    = challenge08

RM    = rm -f

SRC1    = src/hex_to_base64.py
SRC2    = src/xor_combination.py
SRC3    = src/single_xor_cipher.py
SRC4    = src/detect_single_xor.py
SRC5    = src/repeating_xor.py
SRC6    = src/break_repeating_xor.py
SRC7	= src/aes_in_ecb.py
SRC8    = src/detect_aes_in_ecb.py

CFLAGS = -I 
CFLAGS += -Wall -Wextra

all: $(NAME1) $(NAME2) $(NAME3) $(NAME4) $(NAME5) $(NAME6) $(NAME7) $(NAME8)

$(NAME1): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC1)
		cp $(SRC1) $(NAME1)
		chmod 777 $(NAME1)

$(NAME2): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC2)
		cp $(SRC2) $(NAME2)
		chmod 777 $(NAME2)

$(NAME3): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC3)
		cp $(SRC3) $(NAME3)
		chmod 777 $(NAME3)

$(NAME4): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC4)
		cp $(SRC4) $(NAME4)
		chmod 777 $(NAME4)

$(NAME5): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC5)
		cp $(SRC5) $(NAME5)
		chmod 777 $(NAME5)

$(NAME6): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC6)
		cp $(SRC6) $(NAME6)
		chmod 777 $(NAME6)
		
$(NAME7): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC7)
		cp $(SRC7) $(NAME7)
		chmod 777 $(NAME7)

$(NAME8): $(OBJS)
		perl -pi -e 's/\r//g' $(SRC8)
		cp $(SRC8) $(NAME8)
		chmod 777 $(NAME8)

clean:
		$(RM) $(NAME1) $(NAME2) $(NAME3) $(NAME4) $(NAME5) $(NAME6) $(NAME7) $(NAME8)

fclean: clean
		$(RM) $(NAME1) $(NAME2) $(NAME3) $(NAME4) $(NAME5) $(NAME6) $(NAME7) $(NAME8)

re: fclean all

.PHONY: all clean fclean re