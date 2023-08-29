/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:10:09 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/29 16:17:56 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mysleep(unsigned long time)
{
	unsigned long	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(20);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_params	*philos_data;
	pthread_t	*philos_thread;

	philos_data = NULL;
	philos_thread = NULL;
	if (!valid_params(&params, argc, argv))
		return (0);
	if (!init_prog(&params, &philos_data, &philos_thread))
		return (0);
	free_mem(&params, &philos_data, &philos_thread);
	return (0);
}
