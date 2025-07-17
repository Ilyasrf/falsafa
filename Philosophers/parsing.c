/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irfei <irfei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:11:39 by irfei             #+#    #+#             */
/*   Updated: 2025/07/14 18:03:57 by irfei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_numeric_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		int	j;
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_arg_to_config(t_const_philo *config, char **argv)
{
	if (is_valid_numeric_args(argv))
		return (exit_error());
	config->total_ate = 0;
	config->time = get_current_time();
	config->num_philo = ft_atoi(argv[1]);
	config->time_die = ft_atoi(argv[2]);
	config->time_eat = ft_atoi(argv[3]);
	config->time_sleep = ft_atoi(argv[4]);
	if (config->num_philo <= 0 || config->time_die <= 0
		|| config->time_eat <= 0 || config->time_sleep <= 0)
		return (1);
	if (argv[5])
	{
		config->must_eat = ft_atoi(argv[5]);
		if (config->must_eat <= 0)
			return (1);
	}
	else
		config->must_eat = -1;
	return (0);
}

void	initialize_philos(t_philo *philos, t_const_philo *config,
	pthread_mutex_t *forks, pthread_mutex_t *print_lock)
{
	int	i;

	i = 0;
	while (i < config->num_philo)
	{
		philos[i].ate = 0;
		philos[i].id = i + 1;
		philos[i].mutex = forks;
		philos[i].print = print_lock;
		philos[i].var = config;
		i++;
	}
}

int	clean_up_resources(t_philo *philos, pthread_mutex_t *forks, t_const_philo *config)
{
	if (philos)
		free(philos);
	if (forks)
		free(forks);
	if (config)
		free(config);
	return (1);
}

int	set_simul_params(t_philo *philos, t_const_philo *config)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * config->num_philo);
	if (!forks || !philos)
		return (clean_up_resources(philos, forks, config));
	while (i < config->num_philo)
		if (pthread_mutex_init(&forks[i++], 0))
			return (clean_up_resources(philos, forks, config));
	if (pthread_mutex_init(&print_lock, 0))
		return (clean_up_resources(philos, forks, config));
	initialize_philos(philos, config, forks, &print_lock);
	return (0);
}
