/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:36:10 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/07 21:36:52 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_X
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

int	ft_atoi(const char *str);

typedef struct s_shared {
	int				*forks;
	int				death;
	unsigned long			start;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*shared_mutex;
}	t_shared;

typedef struct s_params {
	int			n_philos;
	int			t_die;
	int			t_eat;
	unsigned long		death_time;
	int			t_sleep;
	int			id;
	int			reset;
	int			dead;
	int			must_eat;
	int			full;
	struct timeval	time;
	t_shared	*shared_data;
}	t_params;

#endif