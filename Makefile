# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/15 00:00:00 by root              #+#    #+#              #
#    Updated: 2026/08/28 14:18:59 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CPPFLAGS = -Iincludes -Ilib/includes -Imlx
LDFLAGS = -Llib -Lmlx
LDLIBS = -lmlx -lXext -lX11 -lm -lft
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
LDLIBS += -lbsd
endif
BUILD_DIR = build
SRCS = src/main.c \
		src/init/init_game.c \
		src/parsing/parse_file.c \
		src/parsing/parse_map.c \
		src/render/draw.c \
		src/render/raycaster.c \
		src/render/texture.c \
		src/movement/input.c \
		src/movement/movement.c \
		src/movement/rotation.c \
		src/utils/error.c \
		src/utils/free.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) lib/libft.a mlx/libmlx.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c includes/cub3d.h | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

lib/libft.a:
	$(MAKE) -C lib lib

mlx/libmlx.a:
	$(MAKE) -C mlx

clean:
	$(RM) -r $(BUILD_DIR)
	$(MAKE) -C lib lib_clean
	$(MAKE) -C mlx clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C lib lib_fclean
	$(MAKE) -C mlx clean

re: fclean all

.PHONY: all clean fclean re