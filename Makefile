NAME = minishell
CC = cc 
# CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address
LDFLAGS = -L$(LIBFT_DIR) -L$(PRINTF_DIR) -lreadline -lft -lftprintf

SRC_DIR = srcs
BUILTIN_DIR = srcs/builtin
UTILS_DIR = srcs/utils

SRC = $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(BUILTIN_DIR)/*.c)
SRC += $(wildcard $(UTILS_DIR)/*.c)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ./printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
READLINE_DIR = $(shell brew --prefix readline)
INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I $(RLDIR)/include
OBJ = $(SRC:.c=.o)

RM = rm -rf

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) 

$(LIBFT):
	$(MAKE) -j4 -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -j4 -C $(PRINTF_DIR)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

all: $(NAME)

clean:
	$(RM) $(SRC:.c=.o) cmp out *.txt tmp*

fclean: clean
	$(RM) $(NAME)

test: all
	./tests/test.sh assert

mini: all
	./tests/test.sh minishell

bash: all
	./tests/test.sh bash

re: fclean all

.PHONY: all clean fclean re mini bash