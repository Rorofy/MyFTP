##
## EPITECH PROJECT, 2021
## NWP
## File description:
## Makefile
##

SRC =	src/server/main.c 		\
		src/server/server.c		\
		src/server/utils.c		\
		src/server/client.c		\
		src/server/commands.c	\
		src/server/commands2.c	\
		src/server/commands3.c

CC = gcc
CCFLAGS = -I./include -g

NAME = myftp

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CCFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test

debug: CCFLAGS += -ggdb
debug: all