/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:20:24 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/27 20:24:06 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_params *data)
{
	if (gettime() >= data->death_time)
	{
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death == 0)
		{
			printf("%lums %d died\n", \
				gettime() - data->shared_data->start, data->id);
			data->shared_data->death = data->id;
		}
		if (data->shared_data->death != data->id)
		{
			pthread_mutex_unlock(&data->shared_data->death_lock);
			pthread_mutex_unlock(&data->lock_philo);
			return (0);
		}
		pthread_mutex_unlock(&data->shared_data->death_lock);
		pthread_mutex_unlock(&data->lock_philo);
		return (0);
	}
	return (1);
}

int	check_full(t_params *data)
{
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death != 0)
	{
		pthread_mutex_unlock(&data->shared_data->death_lock);
		pthread_mutex_unlock(&data->lock_philo);
		return (0);
	}
	pthread_mutex_unlock(&data->shared_data->death_lock);
	if (data->full != 0)
	{
		pthread_mutex_unlock(&data->lock_philo);
		return (0);
	}
	else
		pthread_mutex_unlock(&data->lock_philo);
	return (1);
}