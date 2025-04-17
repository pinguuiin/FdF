BBLACK=\033[1;30m
BRED=\033[1;31m
BGREEN=\033[1;32m
BYELLOW=\033[1;33m
BBLUE=\033[1;34m
BPURPLE=\033[1;35m
BCYAN=\033[1;36m
BWHITE=\033[1;37m
RESET_COLOR=\033[0m

NAME = fdf
CC = cc
FLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./src/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DPDS = $(wildcard $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h)
LIBMLX_DIR = ./src/MLX42
LIBMLX = $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
HEADERS = -I./include -I$(LIBMLX_DIR)/include -I$(LIBFT_DIR)
SRC_DIR = ./src
OBJ_DIR = ./obj

SRC_FILES = main.c \
			parse_map.c \
			draw_line.c \
			color_pixel.c \
			array_to_coordinates.c\
			draw_grid.c \
			utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: libmlx $(NAME)

libmlx:
		if [ ! -d "$(LIBMLX_DIR)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX_DIR); fi
		@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(LIBFT): $(LIBFT_DPDS)
		@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./include/fdf.h
		@mkdir -p $(OBJ_DIR)
		$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
		@echo "$(BGREEN) Compiled $^ $(RESET_COLOR)"

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(HEADERS) -o $(NAME)
		@echo "$(BPURPLE) Linked $(RESET_COLOR)"

clean:
		@make clean -C $(LIBFT_DIR)
		rm -rf $(OBJ_DIR)
		@rm -rf $(LIBMLX_DIR)/build
		@echo "$(BBLUE) Cleaned .o files $(RESET_COLOR)"

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)
		@echo "$(BBLUE) Cleaned all $(RESET_COLOR)"

re: fclean all

.PHONY: all clean fclean re libmlx
