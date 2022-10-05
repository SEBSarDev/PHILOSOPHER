/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:08:13 by ssar              #+#    #+#             */
/*   Updated: 2021/09/23 16:04:36 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_usage(void)
{
	write(2, "usage :\n", 8);
	write(2, "./philo  ", 9);
	write(2, "nb_philo  time_die  time_eat  time_sleep  [max_meal]\n", 53);
	return (0);
}

int	ft_free_th(t_philo *phil, int max, int t)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		free(phil->tab[i]->thread);
		pthread_mutex_destroy(&phil->tab[i]->fork);
		pthread_mutex_destroy(&phil->tab[i]->block_dead);
		free(phil->tab[i]);
	}
	if (t == 1)
	{
		pthread_mutex_destroy(&phil->tab[i]->fork);
		pthread_mutex_destroy(&phil->tab[i]->block_dead);
		free(phil->tab[i]);
	}
	free(phil->tab);
	return (0);
}

int	ft_free_all(t_philo *phil, int max, int nb)
{
	free(phil->death);
	pthread_mutex_destroy(&phil->increase);
	pthread_mutex_destroy(&phil->msg);
	ft_free_th(phil, max, nb);
	return (0);
}

int	ft_error(t_philo *phil, char *str, int max, int nb)
{
	write(2, &str, ft_len(str));
	write(2, "\n", 1);
	ft_free_all(phil, max, nb);
	return (0);
}
