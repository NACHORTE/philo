/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:10:09 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/08 14:28:09 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*left_to_die(void *params)
{
	t_params		*data;
	//struct timeval	time_1;
	//struct timeval	time_2;
	//long			diff;
	int				i;

	data = (t_params *)params;
	//while (data->shared_data->death == 0 && data->full == 0)		//mientras que no haya comido todas las veces o siga vivo
	//{
		//gettimeofday(&time_1, NULL);
	//	data->reset = 0;
		while (/*data->reset == 0 &&*/ data->shared_data->death == 0 && data->full == 0)
		{
			//gettimeofday(&time_2, NULL);
			//diff = ((time_2.tv_sec * 1000) + (time_2.tv_usec / 1000)) - ((time_1.tv_sec * 1000) + (time_1.tv_usec / 1000));
			if (gettime() >= data->death_time /*&& data->reset == 0*/)
			{
				pthread_mutex_lock(&data->shared_data->death_lock);
				data->dead = 1;
				if (data->shared_data->death == 0)
				{
					printf("%lu %d died\n", gettime() - data->shared_data->start,data->id);
					data->shared_data->death = data->id;
				}
				if (data->shared_data->death != data->id)
				{
					pthread_mutex_unlock(&data->shared_data->death_lock);
					break;
				}
				pthread_mutex_unlock(&data->shared_data->death_lock);
				//printf("%lu %d\n", diff, data->id);
			}
			usleep(10);
		}
		/*if (data->shared_data->death == 0)
			printf("Reset time philo %d.\n", data->id);*/
	//}
	if (data->shared_data->death == data->id)
	{
		//printf("%lums %d died\n", gettime() - data->shared_data->start,data->id);
		//pthread_mutex_unlock(&data->shared_data->death_lock);
		i = 0;
		while (i < data->n_philos)
		{
			if (data->shared_data->forks[i] != 0)
			{
				pthread_mutex_unlock(&data->shared_data->shared_mutex[i]);
				data->shared_data->forks[i] = 0;	
			}
			i++;
		}
		//data->shared_data.shared_mutex
	}
	return ((void *)0);
}

void	*alive(void *params)
{
	t_params	*data; 								//tenemos shared data a la que acceden todos y params que son los privados.
	t_shared	*shared_data;
	int			id;
	pthread_t	counter;
	int			i;
	
	data = (t_params *)params;
	shared_data = data->shared_data;
	id = data->id;
	data->death_time = data->t_die + gettime();
	pthread_create(&counter, NULL, left_to_die, data);
	/*printf("%d: Estoy vivo!\n", id);
	for(int i = 0; i<6; i++)
	{
		printf("%d: leyendo tenedor %d = %d\n",id, i, shared_data->forks[i]);
	}*/
	if (data->must_eat == 0)
		i = -100;
	else
		i = 0;
	//data->death_time = data->t_die + gettime();
	if ((data->id % 2) == 0)
		//usleep(data->t_eat * 1000 * 0.9);
		usleep(100);
	//printf("philo %d alive %lums\n", id, gettime() - data->shared_data->start);
	while(data->shared_data->death == 0 && i < data->must_eat)								//cada filosofo intenta coger los dos tenedores y los bloquea, come y los desbloquea
	{
		while(1)
		{
		pthread_mutex_lock(&shared_data->shared_mutex[id-1]);
		if (data->shared_data->death != 0)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
			break;
		}
		shared_data->forks[id-1] = id;
		printf("%lu ms %d has taken a fork\n", gettime() - data->shared_data->start, id);
		if (data->n_philos == 1)
			usleep(data->t_die * 1000 + 1000);
		if (id == data->n_philos)
		{
			/*if (shared_data->forks[0] != 0)
			{
				pthread_mutex_unlock(&shared_data->shared_mutex[id - 1]);
				shared_data->forks[id-1] = 0;
				usleep(1000);
				break;
			}*/
			pthread_mutex_lock(&shared_data->shared_mutex[0]);
			if (data->shared_data->death != 0)
			{
				pthread_mutex_unlock(&shared_data->shared_mutex[0]);
				break;
			}
			shared_data->forks[0] = id;
		}
		else
		{
			/*if (shared_data->forks[id] != 0)
			{
				pthread_mutex_unlock(&shared_data->shared_mutex[id - 1]);
				shared_data->forks[id-1] = 0;
				usleep(data->t_eat * 500);
				break;
			}*/
			pthread_mutex_lock(&shared_data->shared_mutex[id]);
			if (data->shared_data->death != 0)
			{
				pthread_mutex_unlock(&shared_data->shared_mutex[id]);
				break;
			}
			shared_data->forks[id] = id;
		}
		printf("%lu ms %d has taken a fork\n", gettime() - data->shared_data->start, id);
		data->death_time = data->t_die + gettime();
		printf("%lu ms %d is eating\n", gettime() - data->shared_data->start, id);
		data->reset = 1;
		if (data->must_eat != 0)
			i++;
		usleep(data->t_eat * 1000);
		//data->reset = 1;
		/*gettimeofday(&data->time, NULL);
		printf("%lums %d has eaten.\n", data->time.tv_usec, id);*/
		pthread_mutex_unlock(&shared_data->shared_mutex[id-1]);
		printf("%lu ms %d droped right fork\n", gettime() - data->shared_data->start, id);
		shared_data->forks[id-1] = 0;
		if (id == data->n_philos)
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[0]);
			shared_data->forks[0] = 0;
			printf("%lu ms %d droped left fork\n", gettime() - data->shared_data->start, id);
		}
		else
		{
			pthread_mutex_unlock(&shared_data->shared_mutex[id]);
			shared_data->forks[id] = 0;
			printf("%lu ms %d droped left fork\n", gettime() - data->shared_data->start, id);
		}
		if (data->shared_data->death != 0)
			break;
		if (i == data->must_eat)
			data->full = 1;
		printf("%lu ms %d is sleeping.\n", gettime() - data->shared_data->start, id);
		usleep(data->t_sleep * 1000);
		break;
		}
		/*if (data->must_eat == 0)
			i = -1;*/
	}
	return ((void *)0);
}

/*int	looking(void *)
{
	t_shared	*public;
	
	public = (t_shared *)shared_data;
	while (1)
	{
		if (public->death == 1)
		{
			
		}
	}
}*/

int	main(int argc, char **argv)
{
	t_params	params;
	t_params	*philos_data;
	pthread_t	*philos_thread;
	int			i;
	t_shared	shared_data;

	if (argc != 5 && argc != 6)
		return (0);
	params.n_philos = ft_atoi(argv[1]);
	params.t_die = ft_atoi(argv[2]);
	params.t_eat = ft_atoi(argv[3]);
	params.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params.must_eat = ft_atoi(argv[5]);
	else
		params.must_eat = 0;
	if (params.n_philos <= 0)
	{
		printf("Please enter a correct number of philosophers.\n");
		return (0);
	}
	philos_thread = malloc(sizeof(pthread_t) * params.n_philos);			//primero reservamos memoria para todos los hilos
	philos_data = malloc(sizeof(t_params) * params.n_philos);				//reservamos memoria para los datos privados
	params.shared_data = &shared_data;										//apuntamos a la misma region de memoria en todos los shared data
	shared_data.forks = malloc(sizeof(int) * params.n_philos);				//creamos todos los tenedores y un mutex para cada uno
	shared_data.shared_mutex = malloc(sizeof(pthread_mutex_t) * params.n_philos);
	shared_data.death = 0;
	params.full = 0;
	i = 0;
	pthread_mutex_init(&params.shared_data->death_lock, NULL);
	while (i < params.n_philos)
	{
		shared_data.forks[i] = 0;
		pthread_mutex_init(&shared_data.shared_mutex[i], NULL);
		i++;
	}
	
	i = 0;
	//pthread_create(supervisor, NULL, looking, &shared_data);
	params.shared_data->start = gettime();
	while (i < params.n_philos)
	{
		params.id = i + 1;
		params.reset = 0;
		params.dead = 0;
		philos_data[i] = params;
		pthread_create(&philos_thread[i], NULL, alive, &philos_data[i]);
		i++;
		usleep(60);
	}
	while (i > 0)
	{
		i--;
		pthread_join(philos_thread[i], NULL);
	}
	return (0);
}
