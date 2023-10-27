/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:10:09 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/27 19:25:39 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mysleep(unsigned long time)
{
	unsigned long	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(100);
}

void	*cheking(void *params)
{
	t_params	*data;
	int			i;
	int			ate;

	data = (t_params *)params;
	i = 0;
	ate = 1;
	while (1)
	{
		if (!check_death(&data[i], &ate))
			break ;
		i++;
		if (i == data->n_philos)
		{
			if (ate == 1)
				break ;
			i = 0;
			ate = 1;
		}
		usleep(100);
	}
	return ((void *)0);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_params	*philos_data;
	pthread_t	*philos_thread;
	int			i;

	philos_data = NULL;
	philos_thread = NULL;
	if (!valid_params(&params, argc, argv))
		return (0);
	if (!init_prog(&params, &philos_data, &philos_thread))
		return (0);
	cheking(philos_data);
	i = 0;
	while (i < params.n_philos)
	{
		if (pthread_join(philos_thread[i], NULL))
		{
			free_mem(&params, &philos_data, &philos_thread);
			return (0);
		}
		i++;
	}
	free_mem(&params, &philos_data, &philos_thread);
	return (0);
}
