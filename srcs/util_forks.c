/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:44:17 by ssar              #+#    #+#             */
/*   Updated: 2021/09/29 10:28:15 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	delock_fork(t_data_phi *data_phi)
{
	pthread_mutex_unlock(&data_phi->ad_tab[data_phi->neighbour]->fork);
	pthread_mutex_unlock(&data_phi->fork);
}

void	first_neighbour_fork(t_philo *phil, t_data_phi *data_phi)
{
	struct timeval	actu;

	pthread_mutex_lock(&data_phi->ad_tab[data_phi->neighbour]->fork);
	print(phil, "steals neighbour's fork", data_phi->num + 1);
	pthread_mutex_lock(&data_phi->fork);
	pthread_mutex_lock(&data_phi->block_dead);
	gettimeofday(&actu, NULL);
	data_phi->l_eat.tv_sec = actu.tv_sec;
	data_phi->l_eat.tv_usec = actu.tv_usec;
	print(phil, "takes his fork", data_phi->num + 1);
}

void	first_own_fork(t_philo *phil, t_data_phi *data_phi)
{
	struct timeval	actu;

	pthread_mutex_lock(&data_phi->fork);
	print(phil, "takes his fork", data_phi->num + 1);
	pthread_mutex_lock(&data_phi->ad_tab[data_phi->neighbour]->fork);
	pthread_mutex_lock(&data_phi->block_dead);
	gettimeofday(&actu, NULL);
	data_phi->l_eat.tv_sec = actu.tv_sec;
	data_phi->l_eat.tv_usec = actu.tv_usec;
	print(phil, "steals neighbour's fork", data_phi->num + 1);
}
