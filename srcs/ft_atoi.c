/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:51:26 by ssar              #+#    #+#             */
/*   Updated: 2021/09/06 19:41:14 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_inbase(const char c)
{
	int		i;
	char	*base;

	base = "0123456789";
	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_space(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	int				a;
	unsigned int	nbr;

	i = ft_space(str);
	nbr = 0;
	neg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	a = ft_inbase(str[i]);
	while (a != -1)
	{
		nbr = nbr * 10 + a;
		i++;
		a = ft_inbase(str[i]);
	}
	if (neg < 0)
		return (nbr * neg);
	else
		return (nbr);
}
