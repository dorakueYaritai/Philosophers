#include <philosophers.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);

int	update_time_to_die(t_philo *philo, long new_time_to_die)
{
	ft_pthread_mutex_lock(&philo->dead_info->mutex);
	*philo->dead_info->time_to_die = new_time_to_die;
	ft_pthread_mutex_unlock(&philo->dead_info->mutex);
	return (SUCCESS);
}

static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;
	long time;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (check_am_i_dead(philo))
		return (ERROR);
	if (print_time(philo->philo_id, sec_milli, act, NONE) == ERROR)
		return (ERROR);
	if (act == EAT)
	{
		update_time_to_die(philo, sec_milli + philo->time_to_starve);
		usleep((unsigned int)(philo->time_to_eat) * 1000);
	}
	else if (act == SLEEP)
		usleep((unsigned int)(philo->time_to_sleep) * 1000);
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	if (exe_act(philo, EAT) == ERROR)
	{
		put_forks(philo);
		return (ERROR);
	}
	if (put_forks(philo) == ERROR)
		return (ERROR);
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	if (exe_act(philo, SLEEP) == ERROR)
		return (ERROR);
	return (philo_think(philo));
}

static int	philo_think(t_philo *philo)
{
	if (exe_act(philo, THINK) == ERROR)
		return (ERROR);
	if (take_forks(philo) == ERROR)
	{
		return (ERROR);
	}
	return (philo_eat(philo));
}

void	birth_philo_baby(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_time_to_die(philo, sec_milli + philo->time_to_starve);
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	birth_philo_baby(philo);
	philo_think(philo);
	write(1, "done!\n", 6);
	return (NULL);
}
