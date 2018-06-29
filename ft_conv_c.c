/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:58:16 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 16:46:35 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_c(va_list ap, t_fmt para)
{
	char	*arg;
	int		argu;
	int		len;
	int		i;

	argu = va_arg(ap, int);
	len = 1;
	if (para.width > 0)
		len = para.width;
	arg = ft_memalloc(len + 1);
	i = 0;
	while (i < len)
		arg[i++] = ' ';
	if (para.options && ft_strchr(para.options, '-'))
		arg[0] = argu;
	else
		arg[len - 1] = argu;
	return (arg);
}
