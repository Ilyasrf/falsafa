#include "philo.h"

int	ft_atoi(char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > LONG_MAX && sign == 1)
			return (-1);
		if (result > (unsigned long)LONG_MAX + 1 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}

void	destroy_fork_mutexes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->var->num_philo)
		pthread_mutex_destroy(&philos->mutex[i++]);
}

unsigned long	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000UL) + (now.tv_usec / 1000));
}

unsigned long	real_time(t_philo *philo)
{
	return (get_current_time() - philo->var->time);
}

void	print_action(t_philo *philo, unsigned long time, char *action)
{
	pthread_mutex_lock(philo->print);
	printf("%lu	%d %s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->print);
}

