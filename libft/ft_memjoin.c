/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:52:16 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/27 19:26:25 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_memjoin(char *s1, const char *s2, int n1, int n2)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	new = NULL;
	if (!s1)
	{
		if ((new = ft_memalloc(n2 + 1)) == 0)
			return (NULL);
		return (ft_memcpy(new, s2, n2));
	}
	if ((new = ft_memalloc(n1 + n2 + 1)) == 0)
		return (NULL);
	ft_memcpy(new, s1, n1);
	i = n1;
	while (j < n2)
		new[i++] = s2[j++];
	return (new);
}
