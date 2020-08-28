# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/08/25 17:14:02 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
LIBFT = libft/libft.a
FILES = main.c farm_alloc.c ants.c
INCLUDE = libft/includes
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	gcc -o $(NAME) -Wall -Wextra -Werror $(FILES) $(LIBFT) -I $(INCLUDE)
	#@make -C libft

clean:
	#@make clean -C libft

fclean: clean
	rm -f $(NAME)
	#@make fclean -C libft

re: fclean
	make all
