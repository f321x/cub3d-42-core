# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 14:27:39 by fahmadia          #+#    #+#              #
#    Updated: 2024/02/09 15:21:43 by fbock            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d

CC 		:= cc
CFLAGS 	:= -Wall -Wextra -Werror
DFLAGS 	:= -g3 -fsanitize=address
DNAME 	:= cub3d_debug

SRCDIR		:= src
OBJDIR		:= objs

LIBMLX	:= ./libs/MLX42
LIB 	:= -L ./libs/libft_combined -lmylib -L $(LIBMLX)/build -ldl -lglfw -pthread -lm -lmlx42
HEADERS := -I ./includes -I ./libs/libft_combined/includes -I $(LIBMLX)/include/MLX42

SRCS 	:= $(SRCDIR)/main.c\
	$(SRCDIR)/mlx_drawing/drawing_main.c\
	$(SRCDIR)/mlx_handlers/handlers_main.c\
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

OBJS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DOBJS   := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d.o,$(SRCS))
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/map_parsing $(OBJDIR)/mlx_drawing $(OBJDIR)/mlx_handlers $(OBJDIR)/raycasting $(OBJDIR)/map_parsing/parsing $(OBJDIR)/map_parsing/helper $(OBJDIR)/map_parsing/free_memory)

all: libmlx $(NAME)

# we need to fix relinking of this function
libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		mkdir -p libs && \
		git clone --depth 1 --branch v2.3.2 https://github.com/codam-coding-college/MLX42 $(LIBMLX) && \
		cmake -S $(LIBMLX) -B $(LIBMLX)/build && \
		make -C $(LIBMLX)/build -j4; \
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR)/%.d.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(DFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libs/libft_combined
	$(CC) $(CFLAGS) $(LIB) $(HEADERS) $(OBJS) -o $(NAME)

debug: $(DOBJS)
	make -C libs/libft_combined
	# make -C libs/libft debug
	$(CC) $(CFLAGS) $(DFLAGS) $(LIB_DEBUG) $(HEADERS) $(DOBJS) -o $(DNAME)

clean:
	rm -rf $(LIBMLX)/build
	make -C libs/libft_combined clean
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(LIBMLX)
	make -C libs/libft_combined fclean
	rm -rf $(NAME) $(DNAME)

re: fclean all

.PHONY: all, clean, fclean, re, debug



# OBJS_PATH = ./objs
# OBJS = $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))

# CC = cc
# CFLAGS = -c -MMD -g -Wall -Werror -Wextra
# INCLUDE = -I./includes\
# 	-I./libs/mylib/libft\
# 	-I./libs/mylib/get_next_line

# NAME = cub3D
# DEPENDENCIES = $(OBJS:.o=.d)
# MYLIB_PATH = ./libs/mylib
# MYLIB = $(MYLIB_PATH)/libmylib.a

# all: $(NAME)

# $(NAME): $(OBJS) Makefile $(MYLIB)
# 	$(CC) $(OBJS) -L$(MYLIB_PATH) -lmylib -o $(NAME)

# $(OBJS_PATH)/%.o: %.c
# 	mkdir -p $(OBJS_PATH)
# 	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

# $(MYLIB):
# 	cd $(MYLIB_PATH) && make

# clean:
# 	rm -f $(OBJS)
# 	rm -f $(DEPENDENCIES)
# 	rm -rf $(OBJS_PATH)

# fclean: clean
# 	rm -f $(NAME)
# 	cd $(MYLIB_PATH) && make fclean

# re: fclean all

# .PHONEY: all clean fclean re

# -include $(DEPENDENCIES)


