/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:16:47 by ssar              #+#    #+#             */
/*   Updated: 2021/09/29 10:30:12 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_eat(t_philo *phil, t_data_phi *data_phi)
{
	int	stock;

	print(phil, "is eating", data_phi->num + 1);
	pthread_mutex_unlock(&data_phi->block_dead);
	pthread_mutex_lock(&phil->data);
	stock = phil->dead;
	pthread_mutex_unlock(&phil->data);
	if (stock == 0)
		wait_for(&data_phi->l_eat, phil->time_eat);
}

void	get_forks_pair(t_philo *phil, t_data_phi *data_phi)
{
	struct timeval	actu;

	if (data_phi->num % 2 == 0)
		first_own_fork(phil, data_phi);
	else
	{
		usleep(100);
		first_neighbour_fork(phil, data_phi);
	}
	ft_eat(phil, data_phi);
	delock_fork(data_phi);
	print(phil, "is sleeping", data_phi->num + 1);
	gettimeofday(&actu, NULL);
	wait_for(&actu, phil->time_sleep);
	print(phil, "is thinking", data_phi->num + 1);
}

void	get_forks_imp_b(t_philo *phil, t_data_phi *data_phi)
{
	struct timeval	actu;

	first_own_fork(phil, data_phi);
	ft_eat(phil, data_phi);
	delock_fork(data_phi);
	print(phil, "is sleeping", data_phi->num + 1);
	gettimeofday(&actu, NULL);
	wait_for(&actu, phil->time_sleep);
	print(phil, "is thinking", data_phi->num + 1);
	gettimeofday(&actu, NULL);
	wait_for(&actu, phil->time_eat);
}

void	get_forks_imp_c(t_philo *phil, t_data_phi *data_phi)
{
	struct timeval	actu;

	gettimeofday(&actu, NULL);
	wait_for(&actu, phil->time_eat);
	first_neighbour_fork(phil, data_phi);
	ft_eat(phil, data_phi);
	delock_fork(data_phi);
	print(phil, "is sleeping", data_phi->num + 1);
	gettimeofday(&actu, NULL);
	wait_for(&actu, phil->time_sleep);
	print(phil, "is thinking", data_phi->num + 1);
}

void	get_forks_impair(t_philo *phil, t_data_phi *data_phi)
{
	struct timeval	actu;

	if (data_phi->num == phil->nb_philo - 1)
	{
		gettimeofday(&actu, NULL);
		wait_for(&actu, phil->time_eat + phil->time_eat / 2);
		first_neighbour_fork(phil, data_phi);
		ft_eat(phil, data_phi);
		delock_fork(data_phi);
		print(phil, "is sleeping", data_phi->num + 1);
		gettimeofday(&actu, NULL);
		wait_for(&actu, phil->time_sleep);
		print(phil, "is thinking", data_phi->num + 1);
	}
	else if (data_phi->num % 2 == 0 && data_phi->num != phil->nb_philo - 1)
		get_forks_imp_b(phil, data_phi);
	else
		get_forks_imp_c(phil, data_phi);
}
