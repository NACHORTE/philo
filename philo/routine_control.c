/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:10 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/16 11:40:33 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*left_to_die(void *params)
{
	t_params		*data;

	data = (t_params *)params;
	while (1)
	{
		//pthread_mutex_lock(&data->lock_philo);
		/*if (!check_death(data))
			break ;*/
		if (!check_full(data))
			break ;
		mysleep(1);
	}
	return ((void *)0);
}

void	init_routine(t_params *data, int *id, int *i)
{
	*id = data->id;
	//pthread_mutex_init(&data->lock_philo, NULL);
	//data->death_time = data->t_die + gettime();
	//pthread_create(&data->counter, NULL, left_to_die, data);
	if (data->must_eat == 0)
		*i = -100;
	else
		*i = 0;
	if ((data->id % 2) == 0)
		mysleep(10);
}

int	someone_died(t_params *data)
{
	//pthread_mutex_lock(&data->lock_philo);
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death != 0)
	{
		//pthread_mutex_unlock(&data->lock_philo);
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->shared_data->death_lock);
	//pthread_mutex_unlock(&data->lock_philo);
	return (1);
}

int	routine(t_params *data, t_shared *shared_data, int id, int *i)
{
	if (!is_dead(data))
	{
		pthread_mutex_lock(&data->shared_data->death_lock);
		printf("%lums %d is thinking\n", gettime() - data->shared_data->start, id);
		pthread_mutex_unlock(&data->shared_data->death_lock);
	}
	if (!take_rfork(data, shared_data, id))
		return (0);
	if (!take_lfork(data, shared_data, id))
		return (0);
	eat(data, i, id);
	if (!drop_forks(data, shared_data, id))
		return (0);
	go_sleep(data, *i, id);
	return (1);
}

void	*alive(void *params)
{
	t_params	*data;
	t_shared	*shared_data;
	int			id;
	int			i;

	data = (t_params *)params;
	shared_data = data->shared_data;
	init_routine(data, &id, &i);
	while (i < data->must_eat)
	{
		routine(data, shared_data, id, &i);
		if (!someone_died(data))
			break ;
	}
	//if (data->n_philos != 1)
	//	pthread_join(data->counter, NULL);
	//pthread_mutex_destroy(&data->lock_philo);
	return ((void *)0);
}
