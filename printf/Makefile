NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SOURCES = srcs/ft_printf.c
SOURCES += srcs/printf_putchar_fd.c
SOURCES += srcs/printf_putstr_fd.c
SOURCES += srcs/ft_puthex.c
SOURCES += srcs/ft_puthex_uns.c
SOURCES += srcs/printf_putnbr_fd.c
SOURCES += srcs/ft_putnbr_uns_fd.c
SOURCES += srcs/printf_strlen.c


OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCES:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re