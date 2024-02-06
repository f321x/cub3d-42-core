# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 15:54:13 by fbock             #+#    #+#              #
#    Updated: 2024/02/06 16:30:46 by fbock            ###   ########.fr        #
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
