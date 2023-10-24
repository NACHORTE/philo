/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:10 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/24 13:00:21 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_routine(t_params *data, int *id, int *i)
{
	*id = data->id;
	if (data->must_eat == 0)
		*i = -100;
	else
		*i = 0;
	if ((data->id % 2) == 0)
		mysleep(10);
}

int	someone_died(t_params *data)
{
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death != 0)
	{
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->shared_data->death_lock);
	return (1);
}

int	routine(t_params *data, t_shared *shared_data, int id, int *i)
{
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death == 0)
		printf("%lu %d is thinking\n", gettime() - data->shared_data->start, id);
	pthread_mutex_unlock(&data->shared_data->death_lock);
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
	return ((void *)0);
}
