# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrenaudi <urenaudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 14:25:25 by vrenaudi          #+#    #+#              #
#    Updated: 2018/06/28 13:00:08 by vrenaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = libft.a

SRCS = ./ft_atoi.c ./ft_bzero.c ./ft_isalnum.c ./ft_isalpha.c \
	  ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c ./ft_itoa.c \
	  ./ft_memalloc.c ./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c \
	  ./ft_memcpy.c ./ft_memdel.c ./ft_memmove.c ./ft_memset.c \
	  ./ft_putchar.c ./ft_putchar_fd.c ./ft_putendl.c ./ft_putendl_fd.c \
	  ./ft_putnbr.c ./ft_putnbr_fd.c ./ft_putstr.c ./ft_putstr_fd.c \
	  ./ft_strclr.c ./ft_strcmp.c ./ft_strcpy.c ./ft_strdel.c \
	  ./ft_strdup.c ./ft_strequ.c ./ft_striter.c ./ft_striteri.c \
	  ./ft_strjoin.c ./ft_strnjoin.c ./ft_strlcat.c ./ft_strlen.c \
	  ./ft_strmap.c ./ft_strmapi.c ./ft_strncat.c ./ft_strncmp.c \
	  ./ft_strncpy.c ./ft_strnequ.c ./ft_strnew.c ./ft_strnstr.c \
	  ./ft_strrchr.c ./ft_strsplit.c ./ft_strstr.c ./ft_strsub.c \
	  ./ft_strtrim.c ./ft_tolower.c ./ft_toupper.c ./ft_lstnew.c \
	  ./ft_lstadd.c ./ft_lstiter.c ./ft_lstdelone.c ./ft_lstdel.c \
	  ./ft_lstmap.c ./ft_intlen.c ./ft_strtoupper.c ./ft_strtolower.c \
	  ./ft_swapbits.c ./ft_printbits.c ./ft_reversebits.c ./ft_strcat.c \
	  ./ft_strchr.c ./ft_strlenuntilc.c ./ft_lstaddlast.c ./ft_strndup.c \
	  ./ft_lstrmvone.c ./ft_strjoinfree.c ./ft_uns_itoa.c ./ft_unsintlen.c \
	  ./ft_dec_to_octa.c ./ft_dec_to_hex.c ./ft_uintmax_to_hex.c ./ft_strrpc.c

OBJ = $(SRCS:.c=.o)

INCLUDES = -I ./includes

RL = ranlib

RM = rm -rf

AR = ar rc

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCS)
	$(AR) $(NAME) $(OBJ)
	$(RL) $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
