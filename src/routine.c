#include <philosophers.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);

static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	// if (philo->time_to_die < sec_milli && philo->time_to_die != -1)
	if (check_am_i_dead(philo))
	{
		if (act == EAT)
		{
			put_fork(philo, philo->first);
			put_fork(philo, philo->second);
		}
		return (ERROR);
	}
	if (print_time(philo->philo_id, sec_milli, act, NONE) == ERROR)
		return (ERROR);
	if (act == EAT)
	{
		philo->time_to_die = sec_milli + philo->time_to_starve;
		usleep((unsigned int)(philo->time_to_eat) * 1000);
	}
	else if (act == SLEEP)
	{
		usleep((unsigned int)(philo->time_to_sleep) * 1000);
	}
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	if (exe_act(philo, EAT) == ERROR)
	{
		return (ERROR);
	}
	if (put_fork(philo, philo->first))
	{
		return (ERROR);
	}
	if (put_fork(philo, philo->second))
	{
		return (ERROR);
	}
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	if (exe_act(philo, SLEEP) == ERROR)
	{
		return (ERROR);
	}
	return (philo_think(philo));
}

static int	philo_think(t_philo *philo)
{
	if (exe_act(philo, THINK) == ERROR)
	{
		return (ERROR);
	}
	if (take_fork(philo, philo->first) == ERROR)
	{
		put_fork(philo, philo->first);
		return (ERROR);
	}
	if (take_fork(philo, philo->second) == ERROR)
	{
		put_fork(philo, philo->first);
		put_fork(philo, philo->second);
		return (ERROR);
	}
	return (philo_eat(philo));
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	philo_think(philo);
	return (NULL);
}
