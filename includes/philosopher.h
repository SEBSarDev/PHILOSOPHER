/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:37:48 by ssar              #+#    #+#             */
/*   Updated: 2021/09/28 19:18:05 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data_phi
{
	pthread_t			*thread;
	int					num;
	int					neighbour;
	int					meal;
	struct timeval		l_eat;
	pthread_mutex_t		fork;
	pthread_mutex_t		block_dead;
	pthread_mutex_t		data_stop;
	pthread_mutex_t		data_meal;
	int					stop;
	int					dead;
	struct s_data_phi	**ad_tab;
}				t_data_phi;

typedef struct s_philo
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_meal;
	pthread_t		*death;
	t_data_phi		**tab;
	pthread_mutex_t	increase;
	pthread_mutex_t	msg;
	pthread_mutex_t	data;
	pthread_mutex_t	start_dead;
	int				i;
	struct timeval	start;
	int				end;
	int				dead;
}				t_philo;

void	print(t_philo *phil, char *act, int num);
int		ft_usage(void);
int		ft_atoi(const char *str);
int		ft_len(char *str);
int		ft_error(t_philo *phil, char *str, int max, int nb);
int		ft_free_all(t_philo *phil, int max, int nb);
char	*ft_itoa(int n);
time_t	dif_actu_last(struct timeval *last, struct timeval *actu);
void	ft_eat(t_philo *phil, t_data_phi *data_phi);
void	wait_for(struct timeval *stock, int max_eat);
int		init_data(t_philo *phil, int argc, char **argv);
int		check_positive(t_philo *phil, char **argv);
int		not_nb(int argc, char **argv);
void	*is_dead(void *arg);
time_t	dif_actu_last_mic(struct timeval *last, struct timeval *actu);
void	get_forks_impair(t_philo *phil, t_data_phi *data_phi);
void	get_forks_pair(t_philo *phil, t_data_phi *data_phi);
void	first_own_fork(t_philo *phil, t_data_phi *data_phi);
void	first_neighbour_fork(t_philo *phil, t_data_phi *data_phi);
void	delock_fork(t_data_phi *data_phi);
#endif
