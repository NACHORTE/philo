/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iortega- <iortega-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:19:48 by iortega-          #+#    #+#             */
/*   Updated: 2023/08/27 19:31:32 by iortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

long	ft_atoi(const char *str)
{
	long	num;
	int		neg;

	neg = 1;
	num = 0;
	while (ft_isspace(*str) && *str != '\0')
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	if (*str == '+' && neg == 1)
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (num * neg);
		else
			num = 10 * num + *str - '0';
		str++;
	}
	num = num * neg;
	return (num);
}

int	isnum(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	valid_params(t_params *params, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Please enter a valid number of arguments.\n");
		return (0);
	}
	if (!isnum(argv))
	{
		printf("Please enter a valid value.\n");
		return (0);
	}
	params->n_philos = ft_atoi(argv[1]);
	params->t_die = ft_atoi(argv[2]);
	params->t_eat = ft_atoi(argv[3]);
	params->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = 0;
	if (params->n_philos <= 0 || params->t_die < 0 || params->t_eat < 0 \
		|| params->t_sleep < 0 || params->must_eat < 0)
	{
		printf("Please enter a valid value.\n");
		return (0);
	}
	return (1);
}
