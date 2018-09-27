/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:58:16 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/27 17:56:32 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_conv_bzer(t_fmt para, int *cpt)
{
	int		len;
	int		i;
	char	*str;

	len = 1;
	i = 0;
	str = NULL;
	if (para.width > 1)
		len = para.width;
	if ((str = ft_memalloc(len + 1)) == 0)
		return (NULL);
	if (para.options && ft_strchr(para.options, '-'))
	{
		str[0] = '\0';
		(*cpt)++;
		i++;
		while (1 < len--)
		{
			str[i++] = ' ';
			(*cpt)++;
		}
	}
	else
	{
		while (len-- > 1)
		{
			str[i++] = ' ';
			(*cpt)++;
		}
		str[i] = '\0';
		(*cpt)++;
	}
	return (str);
}

char		*ft_conv_c(va_list ap, t_fmt para, int *cpt)
{
	char	*arg;
	int		argu;
	int		len;
	int		i;

	argu = va_arg(ap, int);
	arg = NULL;
	if (argu == 0)
	{
		arg = ft_conv_bzer(para, cpt);
		return (arg);
	}
	len = 1;
	if (para.width > 0)
		len = para.width;
	if ((arg = ft_memalloc(len + 1)) == 0)
		return (NULL);
	i = 0;
	while (i < len)
		arg[i++] = ' ';
	if (para.options && ft_strchr(para.options, '-'))
		arg[0] = argu;
	else
		arg[len - 1] = argu;
	(*cpt) = len;
	return (arg);
}
