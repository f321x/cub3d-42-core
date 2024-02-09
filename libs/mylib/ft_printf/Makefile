# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 19:48:22 by ***REMOVED***          #+#    #+#              #
#    Updated: 2024/02/06 08:57:33 by ***REMOVED***         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = count_num_of_digits.c\
	find_format_spec.c\
	to_power.c\
	ft_printf.c\
	print_c.c\
	print_i.c\
	print_p.c\
	print_percent.c\
	print_s.c\
	print_x.c\
	putnbr_long_int.c\
	print_without_format_spec.c\

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

LIBFT_LIB = ../libft/libft.a

LIBFT = ../libft

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	@make -C $(LIBFT)
	@cp $(LIBFT_LIB) $(NAME)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) -c -g $(CFLAGS) $< -o $@

clean: 
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: 
	@make fclean
	@make fclean -C $(LIBFT)
	@make $(NAME)

.PHONY: all clean fclean re
