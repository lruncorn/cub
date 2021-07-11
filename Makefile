# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/13 13:47:04 by lruncorn          #+#    #+#              #
#    Updated: 2021/04/26 19:27:35 by lruncorn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

PATHLIB = ./libft

SRC = 	start/check_valid_map.c start/make_map.c \
		start/error_message.c	start/make_screen.c \
		start/get_ceiling_floor_data.c	start/parse_config.c \
		start/get_data.c start/pre_start.c \
		start/init.c	start/read_config_file.c \
		ray_casting/draw_sprites.c		ray_casting/init_textures.c	\
		ray_casting/sprites_render.c ray_casting/draw_texture.c	\
		ray_casting/move_player.c		ray_casting/start_rc.c \
		ray_casting/find_size.c		ray_casting/rc.c \
		ray_casting/get_color.c		ray_casting/rc_utils.c \
		utils/utils.c


OBJS = $(SRC:.c=.o)

CC = gcc

MAKE = make
CFLAGS = -Wall -Werror -Wextra -c
MLX_FLAGS = libmlx.dylib -framework Appkit -framework OpenGL


HDR = 	cub3D.h libft/libft.h minilibx_mms/mlx.h

.c.o: $(HDR)
		$(CC) $(CFLAGS) -I$(INC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)	
	make bonus -C libft
	make -C minilibx_mms
	cp minilibx_mms/libmlx.dylib libmlx.dylib
	cp libft/libft.a libft.a
	$(CC) -o $(NAME) $(MLX_FLAGS) $(OBJS) libft.a

debug:	$(OBJS)
	make bonus -C libft
	cp libft/libft.a libft.a
	$(CC) $(MLX_FLAGS) $(SRC) libft.a -g 

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(PATHLIB)
	

fclean: clean
	@rm -f ${NAME}
	@$(MAKE) fclean -C $(PATHLIB)

re: fclean all

.PHONY: all clean fclean re 