/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_octa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:47:15 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/06/21 15:08:08 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dec_to_octa(unsigned int nb)
{
	char			*res;
	unsigned int	save;
	int				size;
	int				cpt;
	int				i;

	cpt = 1;
	size = 1;
	i = 0;
	save = nb;
	while (nb >= 8)
	{
		nb = nb / 8;
		size = size * 8;
		cpt++;
	}
	if ((res = ft_memalloc((cpt + 1))) == 0)
		return (NULL);
	while (cpt > 0)
	{
		res[i++] = ((save / size) % 8) + 48;
		size = size / 8;
		cpt--;
	}
	return (res);
}
