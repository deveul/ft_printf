/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:00:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/26 12:45:43 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	ft_get_type(va_list ap, t_fmt *para)
{
	unsigned long long	arg;

	arg = 0;
	if (para->size)
	{
		if (ft_strstr(para->size, "hh"))
			arg = (unsigned long long)va_arg(ap, unsigned int);
		else if (ft_strstr(para->size, "ll"))
			arg = va_arg(ap, unsigned long long);
		else if (ft_strchr(para->size, 'h'))
			arg = (unsigned long long)va_arg(ap, unsigned int);
		else if (ft_strchr(para->size, 'l'))
			arg = (unsigned long long)va_arg(ap, unsigned long);
		else if (ft_strchr(para->size, 'j'))
			arg = (unsigned long long)va_arg(ap, uintmax_t);
		else if (ft_strchr(para->size, 'z'))
			arg = (unsigned long long)va_arg(ap, size_t);
	}
	else
		arg = (unsigned long long)va_arg(ap, unsigned int);
	return (arg);
}

static char					*ft_get_arg(unsigned long long arg, t_fmt para)
{
	char				*str;
	char				*tmp;
	char				*tmp2;
	int					len;
	int					ulololen;

	if ((str = ft_dec_to_hex(arg, para.conv)) == 0)
		return (NULL);
	ulololen = ft_strlen(str);
	if (para.acy > (len = ulololen))
		len = para.acy;
	if ((tmp2 = ft_dec_to_hex(arg, para.conv)) == 0)
		return (NULL);
	if (para.options && ft_strchr(para.options, '#') && arg != 0)
	{
		len += 2;
		ft_strdel(&str);
		if ((str = ft_strjoin("0x", tmp2)) == 0)
			return (NULL);
	}
	if (para.acy != -1)
	{
		if ((tmp = ft_memalloc(len - ulololen + 1)) == 0)
			return (NULL);
		ft_memset(tmp, '0', (len - ulololen));
		ft_strdel(&str);
		str = ft_strjoinfree(tmp, tmp2);
	}
	ft_strdel(&tmp2);
	if (para.options && ft_strchr(para.options, '#') && arg != 0)
		str[1] = para.conv;
	return (str);
}

static char					*ft_width_is_biggr(char *str, t_fmt *para, int len)
{
	char				*tmp;
	char				*tmp2;

	if ((tmp = ft_memalloc(para->width - len + 1)) == 0)
		return (NULL);
	if (!para->options || (!ft_strchr(para->options, '-') && para->acy != -1)
		|| (!ft_strchr(para->options, '-') && !ft_strchr(para->options, '0')))
	{
		if ((tmp2 = ft_strjoinfreeall
(ft_memset(tmp, ' ', para->width - len), str)) == 0)
			return (NULL);
		return (tmp2);
	}
	if (ft_strchr(para->options, '-'))
	{
		if ((tmp2 = ft_strjoinfreeall
(str, ft_memset(tmp, ' ', para->width - len))) == 0)
			return (NULL);
		return (tmp2);
	}
	if (ft_strchr(para->options, '0'))
	{
		free(tmp);
		if ((tmp = ft_memalloc(para->width + 1)) == 0)
			return (NULL);
		tmp = ft_memset(tmp, '0', para->width);
		len--;
		para->width--;
		while (len >= 0)
			tmp[para->width--] = str[len--];
		if ((ft_strrpc(tmp, para->conv, '0')))
			tmp[1] = para->conv;
	}
	ft_strdel(&str);
	return (tmp);
}

char						*ft_conv_h(va_list ap, t_fmt para)
{
	char				*str;
	unsigned long long	arg;
	int					len;

	arg = ft_get_type(ap, &para);
	if (arg == 0 && para.acy == 0)
	{
		len = para.width;
		if ((str = ft_memalloc(len + 1)) == 0)
			return (NULL);
		ft_memset(str, ' ', len);
		return (str);
	}
	str = ft_get_arg(arg, para);
	len = ft_strlen(str);
	if (len < para.width)
		return (ft_width_is_biggr(str, &para, len));
	return (str);
}
