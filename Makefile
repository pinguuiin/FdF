NAME = fdftest

CC = cc
FLAG = -Wall -Wextra -Werror

SRCS = fdf.c \
		parse_map.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_split.c\
		ft_atoi.c\
		ft_strdup.c\
		ft_isdigit.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAG) -I. -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAG) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
