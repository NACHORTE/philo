/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:20:24 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/28 11:24:08 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_params *data, int *ate)
{
	pthread_mutex_lock(&data->lock_philo);
	if (data->full != 1)
		*ate = 0;
	if (gettime() >= data->death_time)
	{
		pthread_mutex_unlock(&data->lock_philo);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death == 0)
		{
			printf("%lu %d died\n", \
				gettime() - data->shared_data->start, data->id);
			data->shared_data->death = data->id;
			pthread_mutex_unlock(&data->shared_data->death_lock);
		}
		else
			pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
	else
		pthread_mutex_unlock(&data->lock_philo);
	return (1);
}

int	init_mutex(t_params *params)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&params->shared_data->death_lock, NULL) != 0)
		return (0);
	while (i < params->n_philos)
	{
		params->shared_data->forks[i] = 0;
		if (pthread_mutex_init(&params->shared_data->shared_mutex[i], NULL)
			!= 0)
		{
			pthread_mutex_destroy(&params->shared_data->death_lock);
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&params->shared_data->shared_mutex[i]);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}
