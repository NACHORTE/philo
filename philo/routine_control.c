/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:14:10 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/27 19:59:12 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_routine(t_params *data, int *id, int *i)
{
	*id = data->id;
	if (data->must_eat == 0)
		*i = -10;
	else
		*i = 0;
	if ((data->id % 2) == 0)
		mysleep((unsigned long) 50);
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
	i = 0;
	init_routine(data, &id, &i);
	while (i < data->must_eat)
	{
		routine(data, shared_data, id, &i);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&data->shared_data->death_lock);
			break ;
		}
		pthread_mutex_unlock(&data->shared_data->death_lock);
	}
	return ((void *)0);
}
