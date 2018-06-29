/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:19:37 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/28 17:21:51 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_arg_nb(const char *fmt)
{
	int		i;
	int		cpt;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1] && fmt[i + 1] != '%')
			cpt++;
		else if (fmt[i] == '%' && fmt[i + 1] && fmt[i + 1] != '%')
			i++;
		i++;
	}
	return (cpt);
}

int		ft_only_fmt(const char *fmt)
{
	ft_putstr(fmt);
	return (ft_strlen(fmt));
}

void	ft_init_fmt(t_fmt *current)
{
	current->options = NULL;
	current->width = 0;
	current->acy = -1;
	current->size = NULL;
	current->conv = 0;
	current->len = 0;
}

t_fmt	ft_analyze_arg(const char *str)
{
	t_fmt	current;
	int		i;
	int		a;
	int		save;

	ft_init_fmt(&current);
	a = 0;
	i = 0;
	save = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#' || str[i] == '0' || str[i] == ' '))
		i++;
	if (i != 0)
		current.options = ft_memalloc(i + 1);
	while (save < i)
		current.options[a++] = str[save++];
	if (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		save = i;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		current.width = ft_atoi(str + save);
	}
	if (str[i] && str[i] == '.')
	{
		i++;
		if (str[i] && str[i] >= '0' && str[i] <= '9')
			current.acy = ft_atoi(str + i);
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
	}
	a = 0;
	if (str[i] && (str[i] == 'h' || str[i] == 'l' || str[i] == 'j' || str[i] == 'z'))
	{
		a = 0;
		save = i;
		while (str[i] && (str[i] == 'h' || str[i] == 'l' || str[i] == 'j' || str[i] == 'z'))
			i++;
		current.size = ft_memalloc(i - save + 1);
		while (save < i)
			current.size[a++] = str[save++];
	}
	current.conv = str[i++];
	current.len = (i + 1);
	return (current);
}
