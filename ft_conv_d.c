/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:00:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 17:15:14 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_get_arg(int arg, t_fmt para)
{
	char			*str;
	char			*tmp;
	int				len;
	int				intlen;
	int				i;

	intlen = ft_intlen(arg);
	len = intlen;
	if (para.acy > len)
		len = para.acy;
	if (arg < 0 && para.acy >= intlen)
		len++;
	str = ft_memalloc(len + 1);
	if (para.acy == -1)
		return (str = ft_itoa(arg));
	tmp = ft_memalloc(len - intlen + 1);
	ft_memset(tmp, '0', (len - intlen));
	str = ft_strjoin(tmp, ft_itoa(arg));
	if (arg < 0)
		str[0] = '-';
	if (arg < 0 && len != intlen)
		str[len - intlen] = '0';
	return (str);
}

static char		*ft_width_is_bigger(char *str, t_fmt *para, int len)
{
	char			*tmp;

	if ((tmp = ft_memalloc(para->width - len + 1)) == 0)
		return (NULL);
	if (!para->options || (!ft_strchr(para->options, '-') && para->acy != -1)
		|| (!ft_strchr(para->options, '-') && !ft_strchr(para->options, '0')))
		return (ft_strjoin(ft_memset(tmp, ' ', para->width - len), str));
	if (ft_strchr(para->options, '-'))
		return (ft_strjoin(str, ft_memset(tmp, ' ', para->width - len)));
	free(tmp);
	if ((tmp = ft_memalloc(para->width + 1)) == 0)
		return (NULL);
	tmp = ft_memset(tmp, '0', para->width);
	len--;
	para->width--;
	while (len >= 0)
	{
		if (str[len] == '+' || str[len] == ' ' || str[len] == '-')
		{
			tmp[0] = str[len];
			break ;
		}
		tmp[para->width--] = str[len--];
	}
	return (tmp);
}

static char		*ft_len_is_bigger(char *str, t_fmt *para, int len)
{
	if (para->options && str[0] != '-'
		&& (ft_strchr(para->options, '+') || ft_strchr(para->options, ' ')))
	{
		if (ft_strchr(para->options, '+'))
			str = ft_strjoin("+", str);
		if (ft_strchr(para->options, ' ') && !ft_strchr(para->options, '+'))
			str = ft_strjoin(" ", str);
	}
	return (str);
}

char			*ft_conv_int(va_list ap, t_fmt para)
{
	char			*str;
	int				arg;
	int				len;

	arg = va_arg(ap, int);
	if (arg == 0 && para.acy == 0)
	{
		if ((str = ft_memalloc(1)) == 0)
			return (NULL);
		return (str);
	}
	str = ft_get_arg(arg, para);
	len = ft_strlen(str);
	str = ft_len_is_bigger(str, &para, len);
	len = ft_strlen(str);
	if (len < para.width)
		return (ft_width_is_bigger(str, &para, len));
	return (str);
}
