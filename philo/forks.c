/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:49:55 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/24 13:00:08 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_params *data)
{
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death > 0)
	{
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
}

int	take_rfork(t_params *data, t_shared *shared_data, int id)
{
	pthread_mutex_lock(&shared_data->shared_mutex[id - 1]);
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death == 0)
		printf("%lu %d has taken a fork\n", \
			gettime() - data->shared_data->start, id);
	pthread_mutex_unlock(&data->shared_data->death_lock);
	if (data->n_philos == 1)
	{
		pthread_mutex_unlock(&shared_data->shared_mutex[id - 1]);
		mysleep(data->t_die + 10);
		return (0);
	}
	return (1);
}

static int	last_philo(t_params *data, t_shared *shared_data, int id)
{
	pthread_mutex_lock(&shared_data->shared_mutex[0]);
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death == 0)
		printf("%lu %d has taken a fork\n", \
			gettime() - data->shared_data->start, id);
	pthread_mutex_unlock(&data->shared_data->death_lock);
	return (1);
}

int	take_lfork(t_params *data, t_shared *shared_data, int id)
{
	if (id == data->n_philos)
	{
		if (!last_philo(data, shared_data, id))
			return (0);
	}
	else
	{
		pthread_mutex_lock(&shared_data->shared_mutex[id]);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death == 0)
			printf("%lu %d has taken a fork\n", \
				gettime() - data->shared_data->start, id);
		pthread_mutex_unlock(&data->shared_data->death_lock);
	}
	return (1);
}

int	drop_forks(t_params *data, t_shared *shared_data, int id)
{
	pthread_mutex_unlock(&shared_data->shared_mutex[id - 1]);
	if (id == data->n_philos)
		pthread_mutex_unlock(&shared_data->shared_mutex[0]);
	else
		pthread_mutex_unlock(&shared_data->shared_mutex[id]);
	return (1);
}
