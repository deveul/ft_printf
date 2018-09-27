/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:19:37 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/24 19:09:57 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_init_fmt(t_fmt *current)
{
	current->options = NULL;
	current->width = 0;
	current->acy = -1;
	current->size = NULL;
	current->conv = 0;
	current->len = 0;
}

static void		ft_anal_arg3(t_fmt *current, int i, int save, char const *str)
{
	int		a;

	a = 0;
	if (str[i] && (str[i] == 'h' || str[i] == 'l'
				|| str[i] == 'j' || str[i] == 'z'))
	{
		a = 0;
		save = i;
		while (str[i] && (str[i] == 'h' || str[i] == 'l'
					|| str[i] == 'j' || str[i] == 'z'))
			i++;
		current->size = ft_memalloc(i - save + 1);
		while (save < i)
			current->size[a++] = str[save++];
	}
	current->conv = str[i++];
	current->len = (i);
}

static void		ft_anal_arg2(t_fmt *current, int i, int save, char const *str)
{
	if (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		save = i;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		current->width = ft_atoi(str + save);
	}
	if (str[i] && str[i] == '.')
	{
		i++;
		current->acy = 0;
		if (str[i] && str[i] >= '0' && str[i] <= '9')
			current->acy = ft_atoi(str + i);
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
	}
	ft_anal_arg3(current, i, save, str);
}

t_fmt			ft_analyze_arg(const char *str)
{
	t_fmt	current;
	int		i;
	int		a;
	int		save;

	ft_init_fmt(&current);
	a = 0;
	i = 0;
	save = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#'
				|| str[i] == '0' || str[i] == ' '))
		i++;
	if (i != 0)
		current.options = ft_memalloc(i + 1);
	while (save < i)
		current.options[a++] = str[save++];
	ft_anal_arg2(&current, i, save, str);
	return (current);
}
