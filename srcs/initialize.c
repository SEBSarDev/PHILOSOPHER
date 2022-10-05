/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:48:55 by ssar              #+#    #+#             */
/*   Updated: 2021/09/28 19:18:20 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	not_nb(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{	
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (ft_usage());
			j++;
		}
	}
	return (1);
}

int	check_positive(t_philo *phil, char **argv)
{
	phil->nb_philo = ft_atoi(argv[1]);
	phil->time_die = ft_atoi(argv[2]);
	phil->time_eat = ft_atoi(argv[3]);
	phil->time_sleep = ft_atoi(argv[4]);
	if (phil->nb_philo <= 0 || phil->nb_philo > 2147483647)
	{
		write(1, "Error : philosophe argument <= 0 or > INT_MAX\n", 46);
		return (0);
	}
	if (phil->time_die <= 0 || phil->time_die > 2147483647)
	{
		write(1, "Error : time_die argument <= 0 or > INT_MAX\n", 44);
		return (0);
	}
	if (phil->time_eat <= 0 || phil->time_eat > 2147483647)
	{
		write(1, "Error : time_eat argument <= 0 or > INT_MAX\n", 44);
		return (0);
	}
	if (phil->time_sleep <= 0 || phil->time_sleep > 2147483647)
	{
		write(1, "Error : time_sleep argument <= 0 or > INT_MAX\n", 46);
		return (0);
	}
	return (1);
}

int	init_philo(t_philo *phil, int i, struct timeval time)
{
	phil->tab[i] = malloc(sizeof(t_data_phi));
	if (!phil->tab[i])
		return (ft_error(phil, "error malloc\n", i - 1, 0));
	pthread_mutex_init(&phil->tab[i]->fork, NULL);
	pthread_mutex_init(&phil->tab[i]->data_stop, NULL);
	pthread_mutex_init(&phil->tab[i]->data_meal, NULL);
	pthread_mutex_init(&phil->tab[i]->block_dead, NULL);
	phil->tab[i]->thread = malloc(sizeof(pthread_t));
	if (!phil->tab[i]->thread)
		return (ft_error(phil, "error malloc\n", i - 1, 1));
	phil->tab[i]->num = i;
	phil->tab[i]->neighbour = i + 1;
	if (i + 1 == phil->nb_philo)
		phil->tab[i]->neighbour = 0;
	phil->tab[i]->meal = 0;
	phil->tab[i]->stop = 0;
	phil->tab[i]->dead = 0;
	phil->tab[i]->ad_tab = phil->tab;
	phil->tab[i]->l_eat = time;
	return (1);
}

int	init_data_bis(t_philo *phil, struct timeval time)
{
	int	i;

	i = -1;
	while (++i < phil->nb_philo)
	{
		if (init_philo(phil, i, time) == 0)
			return (0);
	}
	pthread_mutex_init(&phil->increase, NULL);
	pthread_mutex_init(&phil->msg, NULL);
	pthread_mutex_init(&phil->data, NULL);
	pthread_mutex_init(&phil->start_dead, NULL);
	return (1);
}

int	init_data(t_philo *phil, int argc, char **argv)
{
	struct timeval	time;

	phil->dead = 0;
	phil->end = 0;
	if (check_positive(phil, argv) == 0)
		return (0);
	phil->death = malloc(sizeof(pthread_t));
	if (!phil->death)
		return (0);
	if (argc == 5)
		phil->max_meal = -1;
	else
		phil->max_meal = ft_atoi(argv[5]);
	phil->tab = (t_data_phi **)malloc(sizeof(t_data_phi *) * phil->nb_philo);
	if (!phil->tab)
		return (0);
	gettimeofday(&time, NULL);
	phil->start.tv_sec = time.tv_sec;
	phil->start.tv_usec = time.tv_usec;
	return (init_data_bis(phil, time));
}
