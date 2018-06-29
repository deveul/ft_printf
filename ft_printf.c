/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:40:28 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 17:16:52 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_print(const char *format, t_fmt *para, char **args, int nb)
{
	char	*str;
	char	*tmp;
	int		size[4];
	int		i;
	int		a;
	int		c;
	int		d;

	i = 0;
	a = 0;
	c = 0;
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
	size[3] = 0;
	size[0] = ft_strlen(format);
	while (i < nb)
	{
		size[1] = size[1] + para[i].len;
		i++;
	}
	i = 0;
	while (i < nb)
	{
		size[2] = size[2] + ft_strlen(args[i]);
		i++;
	}
	size[3] = size[0] - size[1] + size[2];
	if ((str = ft_memalloc(size[3] + 1)) == 0)
		return (0);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			d = 0;
			tmp = args[a];
			while (tmp[d])
			{
				str[c] = tmp[d];
				c++;
				d++;
			}
			i = i + para[a].len;
			a++;
		}
		if (format[i])
		{
			str[c] = format[i];
			c++;
			i++;
		}
	}
	ft_putstr(str);
	return (ft_strlen(str));
}

char	*ft_get_conv(va_list ap, t_fmt arg)
{
	char	*str;

	if (arg.conv == 'd' || arg.conv == 'i')
		str = ft_conv_int(ap, arg);
	if (arg.conv == 's')
		str = ft_conv_str(ap, arg);
	if (arg.conv == 'c')
		str = ft_conv_c(ap, arg);
	if (arg.conv == 'u')
		str = ft_conv_u(ap, arg);
	if (arg.conv == 'o')
		str = ft_conv_o(ap, arg);
	if (arg.conv == 'x' || arg.conv == 'X')
		str = ft_conv_h(ap, arg);
	if (arg.conv == 'p')
	{
		str = ft_conv_p(ap, arg);
	//	str = ft_memalloc(1);
	}
	return (str);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		a;
	int		n;
	t_fmt	*arg;
	char	**top;

	a = 0;
	i = 0;
	if ((n = ft_get_arg_nb(format)) == 0)
		return (ft_only_fmt(format));
	if ((arg = malloc(sizeof(t_fmt) * n)) == 0)
		return (-1);
	if ((top = malloc(sizeof(char*) * (n + 1))) == 0)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			arg[a++] = ft_analyze_arg(format + i);
		}
		i++;
	}
	i = -1;
	while (++i < a)
		top[i] = ft_get_conv(ap, arg[i]);
	va_end(ap);
	return (ft_print(format, arg, top, a));
}
