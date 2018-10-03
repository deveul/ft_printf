# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrenaudi <urenaudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 14:25:25 by vrenaudi          #+#    #+#              #
#    Updated: 2018/10/03 19:28:02 by vrenaudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = libftprintf.a

SRCS = ft_printf.c ft_get_fmt.c ft_conv_c.c ft_conv_d.c ft_conv_h.c \
	   ft_conv_o.c ft_conv_s.c ft_conv_u.c ft_conv_p.c ft_conv_per.c \
	   ft_useful.c ft_conv_wc.c ft_init_struct.c ft_get_type.c ft_conv_ws.c \
	   ft_conv_error.c

OBJ = $(SRCS:.c=.o)

RL = ranlib

RM = rm -rf

AR = ar rc

all: $(NAME)

$(NAME):
	@make -C ./libft
	@$(CC) $(CFLAGS) -c $(SRCS)
	@$(AR) $(NAME) $(OBJ)
	@$(RL) $(NAME)

%.o: %.c

clean:
	@make clean -C ./libft
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@$(RM) $(NAME)

re: fclean all
