# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 14:27:39 by fahmadia          #+#    #+#              #
#    Updated: 2024/02/09 14:38:32 by fbock            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d

CC 		:= cc
CFLAGS 	:= -Wall -Wextra -Werror
DFLAGS 	:= -g3 -fsanitize=address
DNAME 	:= cub3d_debug

SRCDIR		:= src
OBJDIR		:= objs
# TESTDIR		:= test
LIBMLX	:= ./libs/MLX42
LIB 		:= libs/libft/libft.a -lreadline $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIB_DEBUG 	:= libs/libft/libft_debug.a -lreadline
HEADERS = -I./includes -I ./libs/libft/includes -I $(LIBMLX)/include/MLX42

SRCS 	:= $(SRCDIR)/main.c

OBJS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DOBJS   := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d.o,$(SRCS))
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/map_parsing $(OBJDIR)/mlx_drawing $(OBJDIR)/mlx_handlers $(OBJDIR)/raycasting)

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
	make -C libs/libft
	$(CC) $(CFLAGS) $(LIB) $(HEADERS) $(OBJS) -o $(NAME)

debug: $(DOBJS)
	make -C libs/libft debug
	$(CC) $(CFLAGS) $(DFLAGS) $(LIB_DEBUG) $(HEADERS) $(DOBJS) -o $(DNAME)

clean:
	rm -rf $(LIBMLX)/build
	make -C libs/libft clean
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(LIBMLX)
	make -C libs/libft fclean
	rm -rf $(NAME) $(DNAME)

re: fclean all

.PHONY: all, clean, fclean, re, debug

# SRCS = main.c\
# 	parsing_main.c\
# 	parse_type_ids_1.c\
# 	parse_type_ids_2.c\
# 	print_error_message.c\
# 	free.c\
# 	atoi.c\
# 	get_config_file_members.c\
# 	parse_colors.c\
# 	trim.c\
# 	type_id_info.c\
# 	open_config_file.c\

# VPATH = ./src\
# 	./src/map_parsing\
# 	./src/map_parsing/free_memory\
# 	./src/map_parsing/helper\
# 	./src/map_parsing/parsing

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


