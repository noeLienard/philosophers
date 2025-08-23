CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = philo

SRC = main.c init.c utils.c action.c monitor.c routine.c

INCLUDE = philosophers.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJ) -I$(INCLUDE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re