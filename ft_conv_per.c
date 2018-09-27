/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_per.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:58:16 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/26 12:46:34 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_per(t_fmt para)
{
	char	*arg;
	int		len;
	int		i;

	len = 1;
	if (para.width > 0)
		len = para.width;
	if ((arg = ft_memalloc(len + 1)) == 0)
		return (NULL);
	ft_memset(arg, ' ', len);
	i = 0;
	if (para.options && ft_strchr(para.options, '-'))
		arg[0] = '%';
	else if (para.options && ft_strchr(para.options, '0'))
	{
		ft_memset(arg, '0', len);
		arg[len - 1] = '%';
	}
	else
		arg[len - 1] = '%';
	return (arg);
}
