/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_useful.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:05:41 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/24 19:07:01 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_arg_nb(const char *fmt)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			i++;
			while (fmt[i] && !ft_strchr("sSpdDioOuUxXcC%", fmt[i]))
				i++;
			cpt++;
		}
		i++;
	}
	return (cpt);
}

int		ft_only_fmt(const char *fmt)
{
	ft_putstr(fmt);
	return (ft_strlen(fmt));
}
