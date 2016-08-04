#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vklaouse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/13 13:33:41 by vklaouse          #+#    #+#              #
#    Updated: 2016/06/25 10:13:04 by vklaouse         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

SRC = main.c \
		check_error.c \
		read_map.c \
		start_mlx.c \
		raycasting.c \
		draw.c \
		key_hook.c \
		parse_map.c \
		bonus.c \
		move.c

OBJ = $(addprefix $(O_DIR)/,$(SRC:.c=.o))

O_DIR = ./objs

CFLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -rf

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) -o $(NAME) $(OBJ) -L./minilibx_macos -lmlx -framework OpenGL -framework Appkit -L./libft -lft

$(O_DIR)/%.o: %.c
	@mkdir -p $(O_DIR)
	@$(CC) -o $@ -c $<

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(O_DIR)
	@make -C libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re%