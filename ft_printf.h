/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:29:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 13:16:19 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include "./libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_fmt
{
	char	*options;
	int		width;
	int		acy;
	char	*size;
	char	conv;
	int		len;
}				t_fmt;

int			ft_printf(const char *format, ...);
int			ft_get_arg_nb(const char *fmt);
int			ft_only_fmt(const char *fmt);
void		ft_init_fmt(t_fmt *current);
t_fmt		ft_analyze_arg(const char *str);
char		*ft_conv_int(va_list ap, t_fmt para);
char		*ft_conv_str(va_list ap, t_fmt para);
char		*ft_conv_c(va_list ap, t_fmt para);
char		*ft_conv_u(va_list ap, t_fmt para);
char		*ft_conv_o(va_list ap, t_fmt para);
char		*ft_conv_p(va_list ap, t_fmt para);
char		*ft_conv_h(va_list ap, t_fmt para);

#endif
