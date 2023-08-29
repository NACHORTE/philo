/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:10:09 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/29 15:49:59 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mysleep(unsigned long time)
{
	unsigned long	start;

	start = gettime();
	while(gettime() - start < time)
		usleep(20);
}

void	*left_to_die(void *params)
{
	t_params		*data;

	data = (t_params *)params;
		while (1)
		{
			pthread_mutex_lock(&data->lock_philo);
			if (!check_death(data))
				break;
			if (!check_full(data))
				break;
			usleep(20);
		}
	return ((void *)0);
}

void	init_routine(t_params *data, int *id, int *i)
{
	*id = data->id;
	pthread_mutex_init(&data->lock_philo, NULL);
	data->death_time = data->t_die + gettime();
	pthread_create(&data->counter, NULL, left_to_die, data);
	if (data->must_eat == 0)
		*i = -100;
	else
		*i = 0;
	if ((data->id % 2) == 0)
		usleep(100);
}

int	take_Rfork(t_params *data, t_shared *shared_data, int id)
{
	pthread_mutex_lock(&shared_data->shared_mutex[id-1]);
	pthread_mutex_lock(&data->lock_philo);
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death != 0)
	{
		pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
		pthread_mutex_unlock(&data->lock_philo);
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->lock_philo);
	pthread_mutex_unlock(&data->shared_data->death_lock);
	printf("%lums %d has taken R fork\n", gettime() - data->shared_data->start, id);
	if (data->n_philos == 1)
	{
		pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
		pthread_join(data->counter, NULL);
		return (0);
	}
	return (1);
}

int	take_Lfork(t_params *data, t_shared *shared_data, int id)
{
	if (id == data->n_philos)
	{
		pthread_mutex_lock(&shared_data->shared_mutex[0]);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[0]);
			pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
			pthread_mutex_unlock(&data->shared_data->death_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->shared_data->death_lock);
	}
	else
	{
		pthread_mutex_lock(&shared_data->shared_mutex[id]);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[id]);
			pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
			pthread_mutex_unlock(&data->shared_data->death_lock);
			return (0);
		}
		pthread_mutex_unlock(&data->shared_data->death_lock);
	}
	return (1);
}

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

int	drop_forks(t_params *data, t_shared *shared_data, int id)
{
	pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
	if (id == data->n_philos)
		pthread_mutex_unlock(&shared_data->shared_mutex[0]);
	else
		pthread_mutex_unlock(&shared_data->shared_mutex[id]);
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death != 0)
	{
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->shared_data->death_lock);
	return (1);
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

int	someone_died(t_params *data)
{
	pthread_mutex_lock(&data->lock_philo);
	pthread_mutex_lock(&data->shared_data->death_lock);
	if (data->shared_data->death != 0)
	{
		pthread_mutex_unlock(&data->lock_philo);
		pthread_mutex_unlock(&data->shared_data->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->shared_data->death_lock);
	pthread_mutex_unlock(&data->lock_philo);
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
	/*id = data->id;
	pthread_mutex_init(&data->lock_philo, NULL);
	data->death_time = data->t_die + gettime();
	pthread_create(&data->counter, NULL, left_to_die, data);
	if (data->must_eat == 0)
		i = -100;
	else
		i = 0;
	if ((data->id % 2) == 0)
		usleep(100);*/
	init_routine(data, &id, &i);
	while(i < data->must_eat)
	{
		while(1)
		{
		/*pthread_mutex_lock(&shared_data->shared_mutex[id-1]);
		pthread_mutex_lock(&data->lock_philo);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
			pthread_mutex_unlock(&data->lock_philo);
			pthread_mutex_unlock(&data->shared_data->death_lock);
			break;
		}
		pthread_mutex_unlock(&data->lock_philo);
		pthread_mutex_unlock(&data->shared_data->death_lock);
		printf("%lums %d has taken R fork\n", gettime() - data->shared_data->start, id);
		if (data->n_philos == 1)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
			pthread_join(data->counter, NULL);
			break;
		}*/
		if (!take_Rfork(data, shared_data, id))
			break;
		/*if (id == data->n_philos)
		{
			pthread_mutex_lock(&shared_data->shared_mutex[0]);
			pthread_mutex_lock(&data->shared_data->death_lock);
			if (data->shared_data->death != 0)
			{
				pthread_mutex_unlock(&shared_data->shared_mutex[0]);
				pthread_mutex_unlock(&data->shared_data->death_lock);
				break;
			}
			pthread_mutex_unlock(&data->shared_data->death_lock);
		}
		else
		{
			pthread_mutex_lock(&shared_data->shared_mutex[id]);
			pthread_mutex_lock(&data->shared_data->death_lock);
			if (data->shared_data->death != 0)
			{
				pthread_mutex_unlock(&shared_data->shared_mutex[id]);
				pthread_mutex_unlock(&data->shared_data->death_lock);
				break;
			}
			pthread_mutex_unlock(&data->shared_data->death_lock);
		}*/
		if (!take_Lfork(data, shared_data, id))
			break;
		printf("%lums %d has taken L fork\n", gettime() - data->shared_data->start, id);
		/*pthread_mutex_lock(&data->lock_philo);
		data->death_time = data->t_die + gettime();
		printf("%lums %d is eating\n", gettime() - data->shared_data->start, id);
		if (data->must_eat != 0)
			i++;
		pthread_mutex_unlock(&data->lock_philo);
		mysleep(data->t_eat);*/
		eat(data, &i, id);
		/*pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
		if (id == data->n_philos)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[0]);
			printf("%lums %d droped left fork\n", gettime() - data->shared_data->start, id);
		}
		else
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[id]);
			printf("%lums %d droped left fork\n", gettime() - data->shared_data->start, id);
		}
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&data->shared_data->death_lock);
			break;
		}
		pthread_mutex_unlock(&data->shared_data->death_lock);*/
		if (!drop_forks(data, shared_data, id))
			break;
		/*pthread_mutex_lock(&data->lock_philo);
		if (i == data->must_eat)
			data->full = 1;
		pthread_mutex_unlock(&data->lock_philo);
		printf("%lums %d is sleeping.\n", gettime() - data->shared_data->start, id);
		mysleep(data->t_sleep);*/
		go_sleep(data, i, id);
		break;
		}
		/*pthread_mutex_lock(&data->lock_philo);
		pthread_mutex_lock(&data->shared_data->death_lock);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&data->lock_philo);
			pthread_mutex_unlock(&data->shared_data->death_lock);
			break;
		}
		pthread_mutex_unlock(&data->shared_data->death_lock);
		pthread_mutex_unlock(&data->lock_philo);*/
		if (!someone_died(data))
			break;
	}
	if (data->n_philos != 1)
		pthread_join(data->counter, NULL);
	pthread_mutex_destroy(&data->lock_philo);
	return ((void *)0);
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
