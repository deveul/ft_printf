/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:19:37 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/10/03 18:27:06 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_check_flags(t_fmt *current, char c)
{
	if (c == '-')
		current->minus = 1;
	if (c == '+')
		current->plus = 1;
	if (c == '#')
		current->hash = 1;
	if (c == '0')
		current->zero = 1;
	if (c == ' ')
		current->space = 1;
}

static void		ft_anal_arg3(t_fmt *current, int i, int save, char const *str)
{
	int		a;

	a = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#'
				|| str[i] == '0' || str[i] == ' '))
		ft_check_flags(current, str[i++]);
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
	while (str[i] && ft_strchr("-+#0 ", str[i]))
		ft_check_flags(current, str[i++]);
	if (str[i])
		current->conv = str[i++];
	else
		current->conv = -1;
	current->len = (i);
}

static void		ft_anal_arg2(t_fmt *current, int i, char const *str)
{
	int		save;

	save = 0;
	if (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		save = i;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		current->width = ft_atoi(str + save);
	}
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#'
				|| str[i] == '0' || str[i] == ' '))
		ft_check_flags(current, str[i++]);
	if (str[i] && str[i] == '.')
	{
		i++;
		while (str[i] && str[i] == '.')
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

	ft_init_fmt(&current);
	a = 0;
	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#'
				|| str[i] == '0' || str[i] == ' '))
		ft_check_flags(&current, str[i++]);
	ft_anal_arg2(&current, i, str);
	return (current);
}
