/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 17:26:50 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 16:47:34 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_p(va_list ap, t_fmt para)
{
	char		*str;
	char		*tmp;
	void		*arg;
	int			len;

	arg = va_arg(ap, void*);
	len = ft_strlen(ft_uintmax_to_hex((uintmax_t)arg, 'x')) + 2;
	if ((str = ft_memalloc(len + 1)) == 0)
		return (NULL);
	str = ft_strjoin("0x", ft_uintmax_to_hex((uintmax_t)arg, 'x'));
	if (len > para.width)
		return (str);
	if ((tmp = ft_memalloc(para.width - len + 1)) == 0)
		return (NULL);
	if (len < para.width && (!para.options
			|| (para.options && !ft_strchr(para.options, '-'))))
		return (ft_strjoinfree(ft_memset(tmp, ' ', (para.width - len)), str));
	else
		return (ft_strjoinfree(str, ft_memset(tmp, ' ', (para.width - len))));
}
