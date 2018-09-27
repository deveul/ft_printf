/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwcinstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:55:06 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/27 17:43:05 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_get_mask(int len)
{
	char			*tab;

	tab = NULL;
	if (len < 8)
		if (!(tab = ft_strdup("0xxxxxxx")) || MB_CUR_MAX == 1)
			return (NULL);
	if (len >= 8 && len < 12)
		if (!(tab = ft_strdup("110xxxxx10xxxxxx")) || MB_CUR_MAX <= 1)
			return (NULL);
	if (len >= 12 && len < 17)
		if (!(tab = ft_strdup("1110xxxx10xxxxxx10xxxxxx")) || MB_CUR_MAX <= 2)
			return (NULL);
	if (len >= 17 && len < 22)
		if (!(tab = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx")) || MB_CUR_MAX <= 3)
			return (NULL);
	return (tab);
}

static char		*ft_writewchar(char *tab)
{
	int		len;
	int		len2;
	char	*octet[4];
	char	*str;

	len = 0;
	len2 = 0;
	str = ft_memalloc((ft_strlen(tab) / 4) + 1);
	while (tab[len])
	{
		if ((octet[len2] = ft_strndup(&tab[len], 8)) == 0)
			return (NULL);
		len += 8;
		len2++;
	}
	len = 0;
	while (len2 > 0)
	{
		str[len] = (char)ft_bi_to_dec(octet[len]);
		len2--;
		len++;
	}
	return (str);
}

char			*ft_putwcinstr(wchar_t wc)
{
	char			*tab;
	unsigned int	nb;
	char			*bi;
	int				len;
	int				len2;

	nb = (unsigned int)wc;
	bi = ft_dec_to_bi(nb);
	len = ft_strlen(bi);
	if (!(tab = ft_get_mask(len)))
		return (NULL);
	len2 = ft_strlen(tab) - 1;
	len--;
	while (len >= 0 && len2 > 0)
	{
		if (tab[len2] == 'x')
		{
			tab[len2] = bi[len];
			len--;
		}
		len2--;
	}
	ft_strrpcall(tab, 'x', '0');
	ft_strdel(&bi);
	return (ft_writewchar(tab));
}
