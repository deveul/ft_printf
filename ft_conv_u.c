/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:00:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 16:55:06 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_get_arg(unsigned int arg, t_fmt para)
{
	char			*str;
	char			*tmp;
	int				len;
	int				intlen;

	intlen = ft_unsintlen(arg);
	len = intlen;
	if (para.acy > len)
		len = para.acy;
	str = ft_memalloc(len + 1);
	if (para.acy == -1)
		return (str = ft_uns_itoa(arg));
	tmp = ft_memalloc(len - intlen + 1);
	ft_memset(tmp, '0', (len - intlen));
	str = ft_strjoin(tmp, ft_uns_itoa(arg));
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
	}
	return (tmp);
}

char			*ft_conv_u(va_list ap, t_fmt para)
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
	ft_putstr(str);
	return (str);
}
