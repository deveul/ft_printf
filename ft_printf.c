/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:40:28 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/10/03 19:03:32 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_get_conv2(va_list ap, t_fmt *arg, int *cpt)
{
	char	*str;

	str = NULL;
	if (arg->conv == 's' && ((!arg->size)
			|| (arg->size && !ft_strchr(arg->size, 'l'))))
		str = ft_conv_str(ap, *arg, cpt);
	if (arg->conv == 'S')
		str = ft_conv_ws(ap, *arg, cpt);
	if (arg->conv == 's' && arg->size && ft_strchr(arg->size, 'l'))
		str = ft_conv_ws(ap, *arg, cpt);
	if (arg->conv == 'c' && ((!arg->size)
			|| (arg->size && !ft_strchr(arg->size, 'l'))))
		str = ft_conv_c(ap, *arg, cpt);
	if (arg->conv == 'C')
		str = ft_conv_wc(ap, *arg, cpt);
	if (arg->conv == 'c' && arg->size && ft_strchr(arg->size, 'l'))
		str = ft_conv_wc(ap, *arg, cpt);
	if (!ft_strchr("sSpdDioOuUxXcC", arg->conv))
		str = ft_conv_error(*arg);
	return (str);
}

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
	if (!str)
		return (ft_get_conv2(ap, arg, cpt));
	return (str);
}

static int	ft_printf2(va_list ap, t_prf *prf, const char *format)
{
	t_fmt	arg;

	if (prf->cpt[3] == 0)
		prf->cpt[3] = prf->cpt[1];
	prf->cpt[1] = 0;
	arg = ft_analyze_arg(&format[++prf->cpt[0]]);
	if ((prf->tmp = ft_get_conv(ap, &arg, &prf->cpt[1])) == 0)
	{
		if (prf->tmp2)
			ft_putmemstr(prf->tmp2, prf->cpt[3]);
		else
			ft_putmemstr(prf->top, prf->cpt[3]);
		ft_del_prf2(prf, &arg);
		return (-1);
	}
	if (arg.conv != 'c' && arg.conv != 'C'
			&& arg.conv != 'S' && arg.conv != 's')
		prf->cpt[1] = ft_strlen(prf->tmp);
	prf->tmp2 = ft_memdup(prf->top, prf->cpt[2]);
	ft_strdel(&prf->top);
	prf->top = ft_memjoin(prf->tmp2, prf->tmp, prf->cpt[2], prf->cpt[1]);
	ft_del_prf(prf, &arg);
	prf->cpt[0] += arg.len;
	prf->cpt[2] += prf->cpt[1];
	return (1);
}

static void	ft_printf3(t_prf *prf, const char *format)
{
	prf->tmp2 = ft_memdup(prf->top, prf->cpt[2]);
	prf->cpt[3] = prf->cpt[2];
	ft_strdel(&prf->top);
	prf->top = ft_memjoin(prf->tmp2, &format[prf->cpt[0]], prf->cpt[2],
			ft_strlenuntilc(&format[prf->cpt[0]], '%'));
	while (format[prf->cpt[0]] && format[prf->cpt[0]] != '%')
	{
		prf->cpt[0]++;
		prf->cpt[2]++;
	}
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_prf	prf;

	ft_init_prf(&prf);
	if ((prf.cpt[0] = ft_get_arg_nb(format)) == 0)
		return (ft_only_fmt(format));
	prf.cpt[0] = 0;
	va_start(ap, format);
	while (format[prf.cpt[0]])
	{
		if (format[prf.cpt[0]] == '%')
		{
			if ((ft_printf2(ap, &prf, format)) == -1)
				return (-1);
		}
		else
			ft_printf3(&prf, format);
	}
	va_end(ap);
	ft_putmemstr(prf.top, prf.cpt[2]);
	ft_strdel(&prf.tmp2);
	ft_strdel(&prf.top);
	return (prf.cpt[2]);
}
