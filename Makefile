# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ***REMOVED*** <***REMOVED***@student.***REMOVED***.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 14:27:39 by ***REMOVED***          #+#    #+#              #
#    Updated: 2024/02/06 12:54:46 by ***REMOVED***         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c\
	parsing_main.c\
	parse_type_ids_1.c\
	parse_type_ids_2.c\
	print_error_message.c\
	free.c\
	atoi.c\
	get_config_file_members.c\
	parse_colors.c\
	trim.c\
	type_id_info.c\
	open_config_file.c\

VPATH = ./src\
	./src/map_parsing\
	./src/map_parsing/free_memory\
	./src/map_parsing/helper\
	./src/map_parsing/parsing
	
OBJS_PATH = ./objs
OBJS = $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))

CC = cc
CFLAGS = -c -MMD -g -Wall -Werror -Wextra
INCLUDE = -I./includes\
	-I./libs/mylib/libft\
	-I./libs/mylib/get_next_line

NAME = cub3D
DEPENDENCIES = $(OBJS:.o=.d)
MYLIB_PATH = ./libs/mylib
MYLIB = $(MYLIB_PATH)/libmylib.a

all: $(NAME)

$(NAME): $(OBJS) Makefile $(MYLIB)
	$(CC) $(OBJS) -L$(MYLIB_PATH) -lmylib -o $(NAME)

$(OBJS_PATH)/%.o: %.c 
	mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(MYLIB):
	cd $(MYLIB_PATH) && make

clean:
	rm -f $(OBJS)
	rm -f $(DEPENDENCIES)
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)
	cd $(MYLIB_PATH) && make fclean

re: fclean all

.PHONEY: all clean fclean re

-include $(DEPENDENCIES)
