/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 08:57:16 by ssar              #+#    #+#             */
/*   Updated: 2021/09/29 10:33:16 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

time_t	dif_actu_last(struct timeval *last, struct timeval *actu)
{
	time_t		dif_sec;
	suseconds_t	add_micro;
	time_t		res;

	res = 0;
	if (actu->tv_sec > last->tv_sec)
	{
		dif_sec = (actu->tv_sec - last->tv_sec) - 1;
		dif_sec = dif_sec * 1000;
		add_micro = actu->tv_usec + (1000000 - last->tv_usec);
		add_micro = add_micro / 1000;
		res = dif_sec + add_micro;
	}
	else
	{
		add_micro = actu->tv_usec - last->tv_usec;
		add_micro = add_micro / 1000;
		res = add_micro;
	}
	return (res);
}

void	print(t_philo *phil, char *action, int num)
{
	int				stock;
	char			*stock1;
	char			*stock2;
	struct timeval	actu;

	gettimeofday(&actu, NULL);
	stock1 = ft_itoa((int)dif_actu_last(&phil->start, &actu));
	stock2 = ft_itoa(num);
	pthread_mutex_lock(&phil->msg);
	pthread_mutex_lock(&phil->data);
	stock = phil->dead;
	pthread_mutex_unlock(&phil->data);
	if (stock == 0)
	{
		write(1, stock1, ft_len(stock1));
		write(1, " philo ", 7);
		write(1, stock2, ft_len(stock2));
		write(1, " ", 1);
		write(1, action, ft_len(action));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&phil->msg);
	free(stock1);
	free(stock2);
}

time_t	dif_actu_last_mic(struct timeval *last, struct timeval *actu)
{
	time_t		dif_sec;
	suseconds_t	add_micro;
	time_t		res;

	res = 0;
	if (actu->tv_sec > last->tv_sec)
	{
		dif_sec = (actu->tv_sec - last->tv_sec) - 1;
		dif_sec = dif_sec * 1000000;
		add_micro = actu->tv_usec + (1000000 - last->tv_usec);
		res = dif_sec + add_micro;
	}
	else
	{
		add_micro = actu->tv_usec - last->tv_usec;
		res = add_micro;
	}
	return (res);
}

void	wait_for(struct timeval *stock, int max_wait)
{
	struct timeval	actu;
	time_t			res;

	gettimeofday(&actu, NULL);
	res = dif_actu_last_mic(stock, &actu);
	while (res < max_wait * 1000)
	{
		usleep(100);
		gettimeofday(&actu, NULL);
		res = dif_actu_last_mic(stock, &actu);
	}
}
