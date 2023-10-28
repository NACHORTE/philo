/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:37:09 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/28 17:43:19 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	first_allo(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread)
{
	*philos_thread = malloc(sizeof(pthread_t) * params->n_philos);
	if (!*philos_thread)
		return (0);
	*philos_data = malloc(sizeof(t_params) * params->n_philos);
	if (!*philos_data)
	{
		free(*philos_thread);
		return (0);
	}
	params->shared_data = malloc(sizeof(t_shared));
	if (!params->shared_data)
	{
		free(*philos_thread);
		free(*philos_data);
		return (0);
	}
	return (1);
}

int	second_allo(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread)
{
	params->shared_data->forks = malloc(sizeof(int) * params->n_philos);
	if (!params->shared_data->forks)
	{
		free(*philos_thread);
		free(*philos_data);
		free(params->shared_data);
		return (0);
	}
	params->shared_data->shared_mutex = \
		malloc(sizeof(pthread_mutex_t) * params->n_philos);
	if (!params->shared_data->shared_mutex)
	{
		free(*philos_thread);
		free(*philos_data);
		free(params->shared_data);
		free(params->shared_data->forks);
		return (0);
	}
	return (1);
}
