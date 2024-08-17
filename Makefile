NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
 CFLAGS += -g -fsanitize=address
LDFLAGS = -L$(LIBFT_DIR) -L$(PRINTF_DIR) -lreadline -lft -lftprintf

SRC_DIR = srcs
BUILTIN_DIR = srcs/builtin
UTILS_DIR = srcs/utils
GNL_DIR = get_next_line

SRC = $(BUILTIN_DIR)/cd_utils.c \
      $(BUILTIN_DIR)/cd.c \
      $(BUILTIN_DIR)/echo.c \
      $(BUILTIN_DIR)/env.c \
      $(BUILTIN_DIR)/exec_buitin.c \
      $(BUILTIN_DIR)/exit.c \
      $(BUILTIN_DIR)/export_arg.c \
      $(BUILTIN_DIR)/export.c \
      $(BUILTIN_DIR)/pwd.c \
      $(BUILTIN_DIR)/unset.c \
      $(UTILS_DIR)/error.c \
      $(UTILS_DIR)/fd.c \
      $(UTILS_DIR)/free.c \
      $(UTILS_DIR)/support.c \
      $(UTILS_DIR)/support2.c \
      $(UTILS_DIR)/var.c \
      $(SRC_DIR)/expand_utils.c \
      $(SRC_DIR)/expand.c \
      $(SRC_DIR)/heredoc.c \
      $(SRC_DIR)/interpret.c \
      $(SRC_DIR)/lexer_get_token.c \
      $(SRC_DIR)/lexer_get_token2.c \
      $(SRC_DIR)/lexer_syntax.c \
      $(SRC_DIR)/lexer_utils.c \
      $(SRC_DIR)/lexer.c \
      $(SRC_DIR)/minishell.c \
      $(SRC_DIR)/parser_utils.c \
      $(SRC_DIR)/parser.c \
      $(SRC_DIR)/pipe.c \
      $(SRC_DIR)/readline.c \
      $(SRC_DIR)/redirect_utils.c \
      $(SRC_DIR)/redirect.c \
      $(SRC_DIR)/shlvl.c \
      $(SRC_DIR)/signal.c \
      $(SRC_DIR)/signal_heredoc.c \
      $(GNL_DIR)/get_next_line_utils.c \
      $(GNL_DIR)/get_next_line.c \

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = ./printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
READLINE_DIR = $(shell brew --prefix readline)

INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR) -I $(RLDIR)/include
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
	$(RM) $(SRC:.c=.o)
	$(MAKE) clean -j4 -C $(LIBFT_DIR)
	$(MAKE) clean -j4 -C $(PRINTF_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(PRINTF)

test: all
	./tests/test.sh assert

mini: all
	./tests/test.sh minishell

bash: all
	./tests/test.sh bash

re: fclean all

.PHONY: all clean fclean re mini bash
