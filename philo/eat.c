/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:11:15 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/29 16:50:29 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_params *data, int *i, int id)
{
	pthread_mutex_lock(&data->lock_philo);
	data->death_time = data->t_die + gettime();
	printf("%lums %d is eating\n", gettime() - data->shared_data->start, id);
	if (data->must_eat != 0)
		(*i)++;
	pthread_mutex_unlock(&data->lock_philo);
	mysleep(data->t_eat);
}

void	go_sleep(t_params *data, int i, int id)
{
	pthread_mutex_lock(&data->lock_philo);
	if (i == data->must_eat)
		data->full = 1;
	pthread_mutex_unlock(&data->lock_philo);
	printf("%lums %d is sleeping.\n", gettime() - data->shared_data->start, id);
	mysleep(data->t_sleep);
}