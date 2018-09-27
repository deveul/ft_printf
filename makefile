# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrenaudi <urenaudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 14:25:25 by vrenaudi          #+#    #+#              #
#    Updated: 2018/09/26 15:51:07 by vrenaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = libftprintf.a

SRCS = ft_printf.c ft_get_fmt.c ft_conv_c.c ft_conv_d.c ft_conv_h.c \
	   ft_conv_o.c ft_conv_s.c ft_conv_u.c ft_conv_p.c ft_conv_per.c \
	   ft_useful.c ft_conv_wc.c

SRCF = ./libft/*.o

OBJ = $(SRCS:.c=.o)

INCLUDES = -I ./includes

RL = ranlib

RM = rm -rf

AR = ar rc

all: $(NAME)

$(NAME):
	@make -C ./libft
	@$(CC) $(CFLAGS) -c $(SRCS)
	@$(AR) $(NAME) $(OBJ) $(SRCF)
	@$(RL) $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all
