/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:35:28 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/14 22:53:14 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread)
{
	int			i;

	*philos_thread = malloc(sizeof(pthread_t) * params->n_philos);
	*philos_data = malloc(sizeof(t_params) * params->n_philos);
	params->shared_data = malloc(sizeof(t_shared));
	params->shared_data->forks = malloc(sizeof(int) * params->n_philos);
	params->shared_data->shared_mutex = \
		malloc(sizeof(pthread_mutex_t) * params->n_philos);
	params->shared_data->death = 0;
	params->full = 0;
	if (!*philos_thread || !*philos_data || \
		!params->shared_data->forks || !params->shared_data->shared_mutex)
		return (0);
	i = 0;
	pthread_mutex_init(&params->shared_data->death_lock, NULL);
	pthread_mutex_init(&params->shared_data->print, NULL);
	while (i < params->n_philos)
	{
		params->shared_data->forks[i] = 0;
		pthread_mutex_init(&params->shared_data->shared_mutex[i], NULL);
		i++;
	}
	return (1);
}

int	init_threads(t_params *params, \
	t_params *philos_data, pthread_t	*philos_thread)
{
	int	i;

	i = 0;
	params->shared_data->start = gettime();
	while (i < params->n_philos)
	{
		params->id = i + 1;
		params->reset = 0;
		philos_data[i] = *params;
		pthread_mutex_init(&philos_data[i].lock_philo, NULL);
		philos_data[i].death_time = philos_data[i].t_die + gettime();
		if (pthread_create(&philos_thread[i], NULL, alive, &philos_data[i]))
			return (0);
		i++;
		//mysleep(1);
	}
	return (1);
}

int	init_prog(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread)
{
	//int	i;

	//i = 0;
	if (!init_data(params, philos_data, philos_thread))
	{
		free_mem(params, philos_data, philos_thread);
		return (0);
	}
	if (!init_threads(params, *philos_data, *philos_thread))
	{
		free_mem(params, philos_data, philos_thread);
		return (0);
	}
	/*while (i < params->n_philos)
	{
		if (pthread_join((*philos_thread)[i], NULL))
		{
			free_mem(params, philos_data, philos_thread);
			return (0);
		}
		i++;
	}*/
	return (1);
}

void	free_mem(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread)
{
	mutex_destroy(params, *philos_data);
	free(params->shared_data->forks);
	free(params->shared_data->shared_mutex);
	free(params->shared_data);
	free(*philos_data);
	free(*philos_thread);
}

void	mutex_destroy(t_params *params, t_params *philos_data)
{
	int	i;

	pthread_mutex_destroy(&params->shared_data->death_lock);
	pthread_mutex_destroy(&params->shared_data->print);
	i = 0;
	while (i < params->n_philos)
	{
		pthread_mutex_destroy(&params->shared_data->shared_mutex[i]);
		pthread_mutex_destroy(&philos_data[i].lock_philo);
		i++;
	}
}
