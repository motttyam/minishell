NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
LDFLAGS = -L$(LIBFT_DIR) -lreadline -lft
SRC = $(wildcard *.c)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)
OBJ = $(SRC:.c=.o)

RM = rm -rf

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) 

$(LIBFT):
	$(MAKE) -j4 -C $(LIBFT_DIR)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

all: $(NAME)

clean:
	$(RM) $(SRC:.c=.o) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re