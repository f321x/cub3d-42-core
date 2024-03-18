# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 14:27:39 by ***REMOVED***          #+#    #+#              #
#    Updated: 2024/03/18 16:19:16 by ***REMOVED***            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d

CC 		:= cc
CFLAGS 	:= -g3 -fsanitize=address -Wall -Wextra -Werror

SRCDIR		:= src
OBJDIR		:= objs

LIBMLX	:= ./libs/MLX42
MLXLIB	:= $(LIBMLX)/build/libmlx42.a
LIB 	:= -L ./libs/libft_combined -lmylib -L $(LIBMLX)/build -ldl -lglfw -pthread -lm -lmlx42
HEADERS := -I ./includes -I ./libs/libft_combined/includes -I $(LIBMLX)/include/MLX42

SRCS 	:= $(SRCDIR)/main.c\
	$(SRCDIR)/mlx_drawing/drawing_main.c\
	$(SRCDIR)/mlx_handlers/handlers_main.c\
	$(SRCDIR)/mlx_handlers/movement_utils.c\
	$(SRCDIR)/mlx_handlers/key_hook_utils.c\
	$(SRCDIR)/mlx_handlers/input_hooks.c\
	$(SRCDIR)/map_parsing/parsing_main.c\
	$(SRCDIR)/map_parsing/parsing/parse_type_ids_1.c\
	$(SRCDIR)/map_parsing/parsing/parse_type_ids_2.c\
	$(SRCDIR)/map_parsing/helper/print_error_message.c\
	$(SRCDIR)/map_parsing/free_memory/free.c\
	$(SRCDIR)/map_parsing/helper/atoi.c\
	$(SRCDIR)/map_parsing/parsing/get_config_file_members.c\
	$(SRCDIR)/map_parsing/parsing/parse_colors.c\
	$(SRCDIR)/map_parsing/parsing/trim.c\
	$(SRCDIR)/map_parsing/parsing/type_id_info.c\
	$(SRCDIR)/map_parsing/parsing/open_config_file.c\
	$(SRCDIR)/map_parsing/parsing/copy_map.c\
	$(SRCDIR)/map_parsing/parsing/copy_map_2.c\
	$(SRCDIR)/map_parsing/parsing/parse_map.c\
	$(SRCDIR)/map_parsing/parsing/parse_map_2.c\
	$(SRCDIR)/raycasting/raycasting_main.c\
	$(SRCDIR)/raycasting/textures.c\
	$(SRCDIR)/raycasting/raycasting_dda.c\
	$(SRCDIR)/mlx_handlers/position_manipulation.c\

OBJS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(MLXLIB) $(NAME)

$(MLXLIB):
	@if [ ! -d "$(LIBMLX)" ]; then \
		mkdir -p $(OBJDIR) $(OBJDIR)/map_parsing $(OBJDIR)/mlx_drawing $(OBJDIR)/mlx_handlers $(OBJDIR)/raycasting $(OBJDIR)/map_parsing/parsing $(OBJDIR)/map_parsing/helper $(OBJDIR)/map_parsing/free_memory && \
		mkdir -p libs && \
		git clone --depth 1 --branch v2.3.2 https://github.com/codam-coding-college/MLX42 $(LIBMLX) && \
		cmake -DDEBUG=1 -S $(LIBMLX) -B $(LIBMLX)/build && \
		make -C $(LIBMLX)/build -j4; \
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libs/libft_combined
	$(CC) $(CFLAGS) $(LIB) $(HEADERS) $(OBJS) -o $(NAME)

clean:
	make -C libs/libft_combined clean
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(LIBMLX)
	make -C libs/libft_combined fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
