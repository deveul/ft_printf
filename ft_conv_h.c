/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:00:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 17:05:47 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_get_arg(unsigned int arg, t_fmt para)
{
	char			*str;
	char			*tmp;
	int				len;
	int				intlen;

	intlen = ft_strlen(ft_dec_to_hex(arg, para.conv));
	if (para.acy > (len = intlen))
		len = para.acy;
	if (para.options && ft_strchr(para.options, '#'))
		len += 2;
	if ((str = ft_memalloc(len + 1)) == 0)
		return (NULL);
	str = ft_dec_to_hex(arg, para.conv);
	if (para.options && ft_strchr(para.options, '#'))
		str = ft_strjoin("0x", str);
	if (para.acy != -1)
	{
		if ((tmp = ft_memalloc(len - intlen + 1)) == 0)
			return (NULL);
		ft_memset(tmp, '0', (len - intlen));
		str = ft_strjoin(tmp, ft_dec_to_hex(arg, para.conv));
	}
	if (para.options && ft_strchr(para.options, '#'))
		str[1] = para.conv;
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
	return (tmp);
}

char			*ft_conv_h(va_list ap, t_fmt para)
{
	char			*str;
	unsigned int	arg;
	int				len;

	arg = va_arg(ap, unsigned int);
	if (arg == 0 && para.acy == 0)
	{
		if ((str = ft_memalloc(1)) == 0)
			return (NULL);
		return (str);
	}
	str = ft_get_arg(arg, para);
	len = ft_strlen(str);
	if (len < para.width)
		return (ft_width_is_bigger(str, &para, len));
	return (str);
}
