# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sboulet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/01 15:00:16 by sboulet           #+#    #+#              #
#    Updated: 2016/04/01 13:26:16 by sboulet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_ssl

CC =		gcc
CFLAGS =	-Wall -Werror -Wextra -g -fsanitize=address -I $(HEADERS)
SRCS =		main.c ssl_errors.c ssl_parse.c ssl_read.c ssl_output.c \
			ssl_base64.c ssl_init.c ssl_free.c \
			ssl_des.c ssl_des_tools.c ssl_des_subkeys.c ssl_des_constantes.c \
			ssl_des_blocks.c ssl_des_function_f.c
OBJS =		$(SRCS:.c=.o)

LIBFT =		./libft
HEADERS =	.

all: lib $(NAME)

lib:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) -L $(LIBFT) -lft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re