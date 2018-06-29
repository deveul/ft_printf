/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:00:24 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 15:53:54 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_get_arg(unsigned int arg, t_fmt para)
{
	char			*str;
	char			*tmp;
	int				len;
	int				intlen;
	int				i;

	intlen = ft_strlen(ft_dec_to_octa(arg));
	len = intlen;
	if (para.acy > len)
		len = para.acy;
	if (para.options && ft_strchr(para.options, '#') && para.acy <= intlen)
		len++;
	str = ft_memalloc(len + 1);
	str = ft_dec_to_octa(arg);
	if (para.options && ft_strchr(para.options, '#') && para.acy <= intlen)
		str = ft_strjoin("0", str);
	if (para.acy == -1)
		return (str);
	tmp = ft_memalloc(len - intlen + 1);
	ft_memset(tmp, '0', (len - intlen));
	str = ft_strjoin(tmp, ft_dec_to_octa(arg));
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

char			*ft_conv_o(va_list ap, t_fmt para)
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
