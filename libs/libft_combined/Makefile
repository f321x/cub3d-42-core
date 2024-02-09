# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbock <fbock@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 15:20:22 by fahmadia          #+#    #+#              #
#    Updated: 2024/02/09 15:22:38 by fbock            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmylib.a
COPY_DEST = ./
OBJS = ./*.o

LIBFT_LIB = ./libft/libft.a
LIBFT = ./libft

GETNEXTLINE_LIB = ./get_next_line/getnextline.a
GETNEXTLINE = ./get_next_line

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(GETNEXTLINE_LIB) extract clean

extract:
	cp $(LIBFT_LIB) $(COPY_DEST)
	cp $(GETNEXTLINE_LIB) $(COPY_DEST)
	ar x ./libft.a
	ar x ./getnextline.a
	ar rcs $(NAME) *.o
	rm -f $(OBJS) "__.SYMDEF SORTED" ./libft.a ./getnextline.a

$(LIBFT_LIB):
	make bonus -C $(LIBFT)

$(GETNEXTLINE_LIB):
	make -C $(GETNEXTLINE)

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFT)
	make fclean -C $(GETNEXTLINE)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make $(NAME)

.PHONY: all clean fclean re
