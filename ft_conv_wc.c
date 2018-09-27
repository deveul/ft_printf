/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_wc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrenaudi <vrenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:58:16 by vrenaudi          #+#    #+#             */
/*   Updated: 2018/09/27 18:09:31 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_conv_bzer(t_fmt para, int *cpt)
{
	int		len;
	int		i;
	char	*str;

	len = 1;
	i = 0;
	str = NULL;
	if (para.width > 1)
		len = para.width;
	if ((str = ft_memalloc(len + 1)) == 0)
		return (NULL);
	if (para.options && ft_strchr(para.options, '-'))
	{
		str[0] = '\0';
		(*cpt)++;
		i++;
		while (1 < len--)
		{
			str[i++] = ' ';
			(*cpt)++;
		}
	}
	else
	{
		while (len-- > 1)
		{
			str[i++] = ' ';
			(*cpt)++;
		}
		str[i] = '\0';
		(*cpt)++;
	}
	return (str);
}

static int	ft_check_arg(int arg)
{
	if ((arg > 55295 && arg < 57344) ||  arg > 1114111)
		return (0);
	return (1);
}

static char	*ft_conv_char(t_fmt para, int *cpt, int argu)
{
	char	*arg;
	int		len;
	int		i;

	arg = NULL;
	len = 1;
	if (para.width > 0)
		len = para.width;
	if ((arg = ft_memalloc(len + 1)) == 0)
		return (NULL);
	i = 0;
	while (i < len)
		arg[i++] = ' ';
	if (para.options && ft_strchr(para.options, '-'))
		arg[0] = argu;
	else
		arg[len - 1] = argu;
	(*cpt) = len;
	return (arg);
}

char		*ft_conv_wc(va_list ap, t_fmt para, int *cpt)
{
	char	*arg;
	char	*tmp;
	char	*tmp2;
	int		len;
	int		save;
	int		argu;

	argu = va_arg(ap, wchar_t);
	if (argu == 0)
		return (ft_conv_bzer(para, cpt));
	if (!ft_check_arg(argu))
		return (NULL);
	if (argu < 256 && MB_CUR_MAX == 1)
		return (ft_conv_char(para, cpt, argu));
	if ((arg = ft_putwcinstr(argu)) == NULL)
		return (NULL);
	len = ft_strlen(arg);
	save = len;
	if (para.width > len)
	{
		len = para.width;
		tmp = ft_strdup(arg);
		ft_strdel(&arg);
		if ((tmp2 = ft_memalloc(len - save + 1)) == 0)
			return (NULL);
		ft_memset(tmp2, ' ', (len - save));
		if (para.options && ft_strchr(para.options, '-'))
			arg = ft_strjoinfreeall(tmp, tmp2);
		else
			arg = ft_strjoinfreeall(tmp2, tmp);
	}
	(*cpt) = len;
	return (arg);
}
