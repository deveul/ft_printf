/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:28:30 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/25 11:37:28 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_charlen(wchar_t wc)
{
	unsigned int	nb;
	unsigned int	len;
	char			*bi;

	nb = (unsigned int)wc;
	bi = ft_dec_to_bi(nb);
	len = ft_strlen(bi);
	ft_strdel(&bi);
	if (len < 8)
		return (nb = 1);
	if (len >= 8 && len < 12)
		return (nb = 2);
	if (len >= 12 && len < 17)
		return (nb = 3);
	if (len >= 17 && len < 22)
		return (nb = 4);
	else
		return (-1);
}
