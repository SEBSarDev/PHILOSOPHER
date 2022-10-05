/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:53:50 by ssar              #+#    #+#             */
/*   Updated: 2021/09/29 22:23:42 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	check_max_meal(t_philo *phil, int *tab, int i)
{
	int	j;
	int	all_end;

	j = -1;
	all_end = 0;
	tab[i] = 1;
	while (++j < phil->nb_philo)
	{
		if (tab[j] == 1)
			all_end++;
	}
	if (all_end == phil->nb_philo)
	{
		i = -1;
		while (++i < phil->nb_philo)
		{
			pthread_mutex_lock(&phil->tab[i]->data_stop);
			phil->tab[i]->stop = 1;
			pthread_mutex_unlock(&phil->tab[i]->data_stop);
		}
		return (1);
	}
	return (0);
}

void	one_is_dead(t_philo *phil, struct timeval now, int *ie)
{
	time_t	r;

	r = dif_actu_last(&phil->start, &now);
	if (phil->max_meal == -1
		|| (phil->max_meal != -1
			&& phil->tab[ie[0]]->meal < phil->max_meal))
	{
		pthread_mutex_lock(&phil->tab[ie[0]]->data_stop);
		phil->tab[ie[0]]->stop = 1;
		pthread_mutex_unlock(&phil->tab[ie[0]]->data_stop);
		print(phil, "is dead", phil->tab[ie[0]]->num + 1);
	}
	pthread_mutex_unlock(&phil->tab[ie[0]]->block_dead);
	pthread_mutex_lock(&phil->data);
	phil->dead = 1;
	pthread_mutex_unlock(&phil->data);
	ie[0] = -1;
	while (++(ie[0]) < phil->nb_philo)
	{
		pthread_mutex_lock(&phil->tab[ie[0]]->data_stop);
		phil->tab[ie[0]]->stop = 1;
		pthread_mutex_unlock(&phil->tab[ie[0]]->data_stop);
		phil->tab[ie[0]]->dead = 1;
	}
}

void	is_dead_bis(t_philo *phil, int *tab_alive, int *ie)
{
	struct timeval	now;
	int				meal;

	ie[0] = -1;
	while (++(ie[0]) < phil->nb_philo && ie[1] == 0)
	{
		pthread_mutex_lock(&phil->tab[ie[0]]->data_meal);
		meal = phil->tab[ie[0]]->meal;
		pthread_mutex_unlock(&phil->tab[ie[0]]->data_meal);
		if (phil->max_meal != -1 && meal >= phil->max_meal)
			ie[1] = check_max_meal(phil, tab_alive, ie[0]);
		if (ie[1] == 1)
			return ;
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&phil->tab[ie[0]]->block_dead);
		if (ie[1] == 0
			&& tab_alive[ie[0]] == 0
			&& dif_actu_last(&phil->tab[ie[0]]->l_eat, &now) >= phil->time_die)
		{
			one_is_dead(phil, now, ie);
			ie[1] = 1;
		}
		if (ie[1] == 0)
			pthread_mutex_unlock(&phil->tab[ie[0]]->block_dead);
	}
}

void	*exit_death(t_philo *phil, int *ie)
{
	ie[0] = -1;
	while (++(ie[0]) < phil->nb_philo)
		phil->tab[ie[0]]->stop = 1;
	ie[1] = 1;
	write(2, "error malloc\n", 13);
	return (NULL);
}

void	*is_dead(void *arg)
{
	int				ie[2];
	t_philo			*phil;
	int				*tab_alive;

	ie[1] = 0;
	phil = (t_philo *)arg;
	tab_alive = (int *)malloc(sizeof(int) * phil->nb_philo);
	if (!tab_alive)
		return (exit_death(phil, ie));
	ie[0] = -1;
	while (++(ie[0]) < phil->nb_philo)
		tab_alive[ie[0]] = 0;
	pthread_mutex_lock(&phil->start_dead);
	pthread_mutex_unlock(&phil->start_dead);
	while (ie[1] == 0)
	{
		is_dead_bis(phil, tab_alive, ie);
		usleep(10);
	}
	free(tab_alive);
	return (NULL);
}
