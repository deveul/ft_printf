/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:40:28 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/27 18:16:14 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


/*static char	*ft_get_conv2(va_list ap, t_fmt *arg)
{
	char	*str;
	//if (arg->conv == 'S')
	//	cpt = ft_conv_wstr(ap, *arg);
	if (arg->conv == 'C')
		str = ft_conv_wc(ap, *arg);
	if (arg->conv == 'c' && arg->size && ft_strchr(arg->size, 'l'))
		str = ft_conv_wc(ap, *arg);
	return (str);
}*/

static char	*ft_get_conv(va_list ap, t_fmt *arg, int *cpt)
{
	char	*str;

	str = NULL;
	if (arg->conv == 'D' || arg->conv == 'O' || arg->conv == 'U')
	{
		arg->conv = arg->conv + 32;
		if ((arg->size = ft_memalloc(2)) == 0)
			return (NULL);
		arg->size[0] = 'l';
	}
	if (arg->conv == 'd' || arg->conv == 'i')
		str = ft_conv_int(ap, *arg);
	if (arg->conv == 'u')
		str = ft_conv_u(ap, *arg);
	if (arg->conv == 'o')
		str = ft_conv_o(ap, *arg);
	if (arg->conv == 'x' || arg->conv == 'X')
		str = ft_conv_h(ap, *arg);
	if (arg->conv == 'p')
		str = ft_conv_p(ap, *arg);
	if (arg->conv == '%')
		str = ft_conv_per(*arg);
	if (arg->conv == 's')
		str = ft_conv_str(ap, *arg);
	if (arg->conv == 'c' && ((!arg->size) || (arg->size && !ft_strchr(arg->size, 'l'))))
		str = ft_conv_c(ap, *arg, cpt);
	if (arg->conv == 'C')
		if ((str = ft_conv_wc(ap, *arg, cpt)) == 0)
			return (NULL);
	if (arg->conv == 'c' && arg->size && ft_strchr(arg->size, 'l'))
		if ((str = ft_conv_wc(ap, *arg, cpt)) == 0)
			return (NULL);
	return (str);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		cpt;
	int		cpt2;
	t_fmt	arg;
	char	*top;
	char	*tmp;
	char	*tmp2;

	top = NULL;
	cpt2 = 0;
	if ((i = ft_get_arg_nb(format)) == 0)
		return (ft_only_fmt(format));
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			cpt = 0;
			i++;
			arg = ft_analyze_arg(&format[i]);
			if ((tmp = ft_get_conv(ap, &arg, &cpt)) == 0)
			{
				ft_putmemstr(tmp2, cpt2);
				return (-1);
			}
			if (arg.conv != 'c' && arg.conv != 'C')
				cpt = ft_strlen(tmp);
			tmp2 = ft_memdup(top, cpt2);
			if (top)
				ft_strdel(&top);
			top = ft_memjoinfreeall(tmp2, tmp, cpt2, cpt);
			i += arg.len;
			cpt2 += cpt;
		}
		else
		{
			tmp2 = ft_memdup(top, cpt2);
			if (top)
				ft_strdel(&top);
			top = ft_memjoin(tmp2 ,&format[i], cpt2, ft_strlenuntilc(&format[i], '%'));
			while (format[i] && format[i] != '%')
			{
				i++;
				cpt2++;
			}
		}
	}
	va_end(ap);
	ft_putmemstr(top, cpt2);
	ft_strdel(&top);
	return (cpt2);
}
