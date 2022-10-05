/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:58:36 by ssar              #+#    #+#             */
/*   Updated: 2021/09/06 19:05:28 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_count_size_nbr(int n)
{
	unsigned int	nbr;

	if (n < 0)
		nbr = (unsigned int)n * (-1);
	else
		nbr = (unsigned int)n;
	if (nbr > 9)
		return (ft_count_size_nbr(nbr / 10) + 1);
	return (1);
}

static void	ft_fill(char *ptr, int size, int n)
{
	char			*dec;
	unsigned int	nbr;

	if (n < 0)
		nbr = (unsigned int)n * (-1);
	else
		nbr = (unsigned int)n;
	dec = "0123456789";
	while (nbr > 9)
	{
		ft_fill(ptr, size - 1, nbr / 10);
		nbr = nbr % 10;
	}
	ptr[size] = dec[nbr];
}

char	*ft_itoa(int n)
{
	int		size;
	char	*ptr;

	size = ft_count_size_nbr(n);
	if (n < 0)
	{
		ptr = (char *)malloc(sizeof(char) * (size + 2));
		if (!ptr)
			return (NULL);
		ptr[0] = '-';
		ft_fill(ptr, size, n);
		ptr[size + 1] = '\0';
	}
	else
	{
		ptr = (char *)malloc(sizeof(char) * (size + 1));
		if (!ptr)
			return (NULL);
		ft_fill(ptr, size - 1, n);
		ptr[size] = '\0';
	}
	return (ptr);
}
