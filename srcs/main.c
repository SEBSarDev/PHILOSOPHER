/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:59:36 by ssar              #+#    #+#             */
/*   Updated: 2021/09/29 22:16:24 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_routine(t_philo *phil, int i)
{
	if (phil->nb_philo % 2 == 0)
		get_forks_pair(phil, phil->tab[i]);
	else
		get_forks_impair(phil, phil->tab[i]);
	pthread_mutex_lock(&phil->tab[i]->data_meal);
	phil->tab[i]->meal++;
	pthread_mutex_unlock(&phil->tab[i]->data_meal);
	usleep(10);
}

void	*boucle(void *arg)
{
	t_philo	*phil;
	int		i;
	int		stop;

	phil = (t_philo *)arg;
	pthread_mutex_lock(&phil->increase);
	i = phil->i;
	phil->i = i + 1;
	pthread_mutex_unlock(&phil->increase);
	pthread_mutex_lock(&phil->tab[i]->data_meal);
	phil->tab[i]->meal = 0;
	pthread_mutex_unlock(&phil->tab[i]->data_meal);
	pthread_mutex_lock(&phil->tab[i]->data_stop);
	stop = phil->tab[i]->stop;
	pthread_mutex_unlock(&phil->tab[i]->data_stop);
	while (stop == 0)
	{
		if (phil->nb_philo > 1 && (phil->max_meal == -1 || (phil->max_meal > -1
					&& phil->tab[i]->meal < phil->max_meal)))
			ft_routine(phil, i);
		pthread_mutex_lock(&phil->tab[i]->data_stop);
		stop = phil->tab[i]->stop;
		pthread_mutex_unlock(&phil->tab[i]->data_stop);
	}
	return (NULL);
}

void	create_threads(t_philo *phil)
{
	int	i;
	int	ret;

	i = -1;
	pthread_mutex_lock(&phil->start_dead);
	ret = pthread_create(phil->death, NULL, is_dead, phil);
	if (ret != 0)
		ft_error(phil, "error pthread creation\n", phil->nb_philo, 0);
	phil->i = 0;
	while (++i < phil->nb_philo)
	{
		ret = pthread_create(phil->tab[i]->thread, NULL, boucle, phil);
		if (ret != 0)
			ft_error(phil, "error pthread creation\n", phil->nb_philo, 0);
	}
	if (phil->nb_philo > 1)
		gettimeofday(&phil->start, NULL);
	pthread_mutex_unlock(&phil->start_dead);
}

int	main(int argc, char **argv)
{
	t_philo	phil;
	int		i;

	if (argc < 5 || argc > 6)
		return (ft_usage());
	if (not_nb(argc, argv) == 0 || init_data(&phil, argc, argv) == 0)
		return (0);
	create_threads(&phil);
	i = -1;
	while (++i < phil.nb_philo)
		pthread_join(*phil.tab[i]->thread, NULL);
	pthread_join(*phil.death, NULL);
	ft_free_all(&phil, phil.nb_philo, 0);
	return (0);
}
