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

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->var->num_philo)
		pthread_mutex_destroy(&philo->mutex[i++]);
}

unsigned long	in_time(void)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l);
}

unsigned long	real_time(t_philo *philo)
{
	return (in_time() - philo->var->time);
}

void	print(t_philo *philo, unsigned long time, char *is_doing)
{
	pthread_mutex_lock(philo->print);
	printf("%lu	%d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->print);
}

