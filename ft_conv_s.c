/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 19:55:42 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/26 12:48:39 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_get_arg(char *arg, t_fmt para)
{
	char	*str;
	int		len;

	len = ft_strlen(arg);
	if (para.acy == -1 || para.acy >= len)
	{
		if ((str = ft_memalloc(len + 1)) == 0)
			return (NULL);
		ft_strcpy(str, arg);
	}
	else
	{
		if ((str = ft_memalloc(para.acy + 1)) == 0)
			return (NULL);
		ft_strncpy(str, arg, para.acy);
	}
	return (str);
}

static char	*ft_fill_str(char *str, t_fmt *para, int len)
{
	char	*tmp;

	if ((tmp = ft_memalloc(para->width - len + 1)) == 0)
		return (NULL);
	if (!para->options || (para->options && !ft_strchr(para->options, '-')))
		return (ft_strjoin(ft_memset(tmp, ' ', (para->width - len)), str));
	return (ft_strjoin(str, ft_memset(tmp, ' ', (para->width - len))));
}

char		*ft_conv_str(va_list ap, t_fmt para)
{
	char	*arg;
	char	*str;
	int		len;

	arg = va_arg(ap, char*);
	if (!arg)
		arg = ft_strdup("(null)");
	str = ft_get_arg(arg, para);
	len = ft_strlen(str);
	if (para.width > len)
		return (ft_fill_str(str, &para, len));
	return (str);
}
