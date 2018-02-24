# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sboulet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 09:58:09 by sboulet           #+#    #+#              #
#*   Updated: 2018/02/24 18:05:27 by jhezard          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME =		libft.a
FLAGS =		-Wall -Werror -Wextra -g
SRCS =		ft_isdigit.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strrchr.c \
			ft_isprint.c ft_putchar.c ft_strclr.c ft_strlen.c ft_strsplit.c \
			ft_itoa.c ft_putchar_fd.c ft_strcmp.c ft_strmap.c ft_strstr.c \
			ft_memalloc.c ft_putendl.c ft_strcpy.c ft_strmapi.c ft_strsub.c \
			ft_memccpy.c ft_putendl_fd.c ft_strdel.c ft_strncat.c ft_strtrim.c \
			ft_atoi.c ft_memchr.c ft_putnbr.c ft_strdup.c ft_strncmp.c \
			ft_tolower.c ft_bzero.c ft_memcmp.c ft_putnbr_fd.c ft_strequ.c \
			ft_strncpy.c ft_toupper.c ft_isalnum.c ft_memcpy.c ft_putstr.c \
			ft_striter.c ft_strnequ.c ft_isalpha.c ft_memdel.c ft_putstr_fd.c \
			ft_striteri.c ft_strnew.c ft_isascii.c ft_memmove.c ft_strcat.c \
			ft_strjoin.c ft_strnstr.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
			ft_lstadd.c ft_lstiter.c ft_lstmap.c get_next_line.c ft_gnl.c\
			ft_memrealloc.c ft_itoa_base.c ft_atoi_base.c ft_atoi_hexa.c \
			ft_tabrev.c ft_intlen.c ft_hex.c
OBJS =		$(SRCS:.c=.o)

all :		$(NAME)

$(NAME) :
			gcc -c $(FLAGS) $(SRCS)
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

clean :
			rm -f $(OBJS)

fclean :	clean
			rm -f $(NAME)

re :		fclean all

.PHONY : all clean fclean re
