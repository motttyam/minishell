NAME = minishell
CC = cc -Wall -Wextra -Werror -g -fsanitize=address
LDFRAGS = -lreadline
SRC = 	minishell.c \
		readline.c \
		lexer.c \
		error.c \
		ft_strchr.c ft_substr.c ft_strlen.c \

OBJ = $(SRC:.c=.o)

RM = rm -rf

%.o:%.c
	$(CC) -c $< -o $@ 

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFRAGS)

all: $(NAME)

clean:
	$(RM) $(SRC:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all
