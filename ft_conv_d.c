/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:00:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/27 13:16:48 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	ft_get_type(va_list ap, t_fmt *para)
{
	long long	arg;

	arg = 0;
	if (para->size)
	{
		if (ft_strstr(para->size, "hh"))
			arg = (char)(long long)va_arg(ap, int);
		else if (ft_strstr(para->size, "ll"))
			arg = va_arg(ap, long long);
		else if (ft_strchr(para->size, 'h'))
			arg = (short)(long long)va_arg(ap, int);
		else if (ft_strchr(para->size, 'l'))
			arg = (long long)va_arg(ap, long);
		else if (ft_strchr(para->size, 'j'))
			arg = (long long)va_arg(ap, intmax_t);
		else if (ft_strchr(para->size, 'z'))
			arg = (long long)va_arg(ap, size_t);
	}
	else
		arg = (long long)va_arg(ap, int);
	return (arg);
}

static char			*ft_get_arg(long long arg, t_fmt para)
{
	char			*str;
	char			*tmp;
	char			*tmp2;
	int				len;
	int				lololen;

	lololen = ft_lololen(arg);
	len = lololen;
	if (para.acy > len)
		len = para.acy;
	if (arg < 0 && para.acy >= lololen)
		len++;
	if (para.acy == -1)
	{
		if ((str = ft_itoa_ll(arg)) == 0)
			return (NULL);
		return (str);
	}
	if ((tmp = ft_memalloc(len - lololen + 1)) == 0)
		return (NULL);
	ft_memset(tmp, '0', (len - lololen));
	tmp2 = ft_itoa_ll(arg);
	if ((str = ft_strjoin(tmp, tmp2)) == NULL)
		return (NULL);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	if (arg < 0)
		str[0] = '-';
	if (arg < 0 && len != lololen)
		str[len - lololen] = '0';
	return (str);
}

static char			*ft_width_is_bigger(char *str, t_fmt *para, int len)
{
	char			*tmp;
	char			*tmp2;

	if ((tmp = ft_memalloc(para->width - len + 1)) == 0)
		return (NULL);
	if (!para->options || (!ft_strchr(para->options, '-') && para->acy != -1)
		|| (!ft_strchr(para->options, '-') && !ft_strchr(para->options, '0')))
	{
		tmp2 = ft_strjoin(ft_memset(tmp, ' ', para->width - len), str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (tmp2);
	}
	if (ft_strchr(para->options, '-'))
	{
		tmp2 = ft_strjoin(str, ft_memset(tmp, ' ', para->width - len));
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (tmp2);
	}
	ft_strdel(&tmp);
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
	ft_strdel(&str);
	return (tmp);
}

static char			*ft_len_is_bigger(char *str, t_fmt *para)
{
	char			*tmp;

	if (para->options && str[0] != '-'
		&& (ft_strchr(para->options, '+') || ft_strchr(para->options, ' ')))
	{
		if (ft_strchr(para->options, '+'))
		{
			tmp = ft_strjoin("+", str);
			ft_strdel(&str);
		}
		if (ft_strchr(para->options, ' ') && !ft_strchr(para->options, '+'))
		{
			tmp = ft_strjoin(" ", str);
			ft_strdel(&str);
		}
		return (tmp);
	}
	return (str);
}

/*static char			*ft_zero(t_fmt para)
{
	char				*str;
	int					len;

	len = para.width;
	if ((str = ft_memalloc(len + 1)) == 0)
		return (NULL);
	ft_memset(str, ' ', len);
	if (para.options && ft_strchr(para.options, '#'))
	{
		if (len == 0)
		{
			ft_strdel(&str);
			if ((str = ft_memalloc(2)) == 0)
				return (NULL);
			str[0] = '0';
		}
		else
			str[--len] = '0';
	}
	return (str);
}*/

char				*ft_conv_int(va_list ap, t_fmt para)
{
	char			*str;
	long long		arg;
	int				len;

	arg = ft_get_type(ap, &para);
	if (arg == 0 && para.acy == 0)
	{
		len = para.width;
		if (para.options && ft_strchr(para.options, '+') && len == 0)
			len++;
		if (para.options && ft_strchr(para.options, ' ')
				&& !(ft_strchr(para.options, '+')) && len == 0)
			len++;
		if ((str = ft_memalloc(len + 1)) == 0)
			return (NULL);
		ft_memset(str, ' ', len);
		if (para.options && ft_strchr(para.options, '+'))
			str[--len] = '+';
		return (str);
	}
	str = ft_get_arg(arg, para);
	len = ft_strlen(str);
	str = ft_len_is_bigger(str, &para);
	len = ft_strlen(str);
	if (len < para.width)
		return (ft_width_is_bigger(str, &para, len));
	return (str);
}
