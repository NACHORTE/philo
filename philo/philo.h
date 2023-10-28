/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:36:10 by iortega-          #+#    #+#             */
/*   Updated: 2023/10/28 17:46:55 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_shared {
	int				*forks;
	int				death;
	unsigned long	start;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*shared_mutex;
}	t_shared;

typedef struct s_params {
	int				n_philos;
	long			t_die;
	long			t_eat;
	unsigned long	death_time;
	long			t_sleep;
	int				id;
	long			must_eat;
	int				full;
	pthread_mutex_t	lock_philo;
	t_shared		*shared_data;
}	t_params;

long			ft_atoi(const char *str);
int				valid_params(t_params *params, int argc, char **argv);
int				isnum(char **argv);
int				init_data(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread);
int				init_threads(t_params *params, \
	t_params *philos_data, pthread_t	*philos_thread);
void			mutex_destroy(t_params *params, t_params *philos_data);
void			free_mem(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread);
unsigned long	gettime(void);
int				init_prog(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread);
void			*alive(void *params);
int				check_death(t_params *data, int *ate);
int				take_rfork(t_params *data, t_shared *shared_data, int id);
int				take_lfork(t_params *data, t_shared *shared_data, int id);
void			eat(t_params *data, int *i, int id);
int				drop_forks(t_params *data, t_shared *shared_data, int id);
void			go_sleep(t_params *data, int i, int id);
void			init_routine(t_params *data, int *id, int *i);
int				routine(t_params *data, t_shared *shared_data, int id, int *i);
void			*alive(void *params);
void			mysleep(unsigned long time);
int				init_mutex(t_params *params);
int				first_allo(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread);
int				second_allo(t_params *params, \
	t_params **philos_data, pthread_t **philos_thread);

#endif