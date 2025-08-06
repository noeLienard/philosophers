CC = cc

CFLAGS = 

NAME = philo

SRC = main.c utils.c action.c $(wildcard ft_printf/*.c)

INCLUDE = philosophers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re