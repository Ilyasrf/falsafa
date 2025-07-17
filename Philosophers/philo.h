
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_all
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}t_const_philo;

typedef struct s_philo
{
	int				ate;
	int				id;
	t_const_philo	*var;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	unsigned long	last_meal;
}t_philo;

int				ft_atoi(char *str);
int				exit_error(void);
int				is_valid_numeric_args(char **argv);
int				parse_arg_to_config(t_const_philo *config, char **argv);
void			initialize_philos(t_philo *philos, t_const_philo *config,
					pthread_mutex_t *forks, pthread_mutex_t *print_lock);
int				clean_up_resources(t_philo *philos, pthread_mutex_t *forks,
					t_const_philo *config);
int				set_simul_params(t_philo *philos, t_const_philo *config);
void			destroy_fork_mutexes(t_philo *philos);
unsigned long	get_current_time(void);
unsigned long	real_time(t_philo *philo);
void			print_action(t_philo *philo, unsigned long time, char *action);
void			*doo(void *p);
void			func(t_philo *philo, t_const_philo *var);

#endif