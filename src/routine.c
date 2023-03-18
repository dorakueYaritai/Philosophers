#include <philosophers.h>
#include <stdlib.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);

static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		print_time(philo->philo_id, philo->time_to_die, DEAD, 0);
	}
	print_time(philo->philo_id, sec_milli, act, NONE);
	if (act == EAT)
	{
		philo->time_to_die = sec_milli + philo->time_to_starve;
		usleep((unsigned int)(philo->time_to_eat) * 1000);
	}
	else if (act == SLEEP)
	{
		usleep((unsigned int)(philo->time_to_sleep) * 1000);
	}
}

static int	philo_eat(t_philo *philo)
{
	exe_act(philo, EAT);
	put_fork(philo, philo->first);
	put_fork(philo, philo->second);
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	exe_act(philo, SLEEP);
	return (philo_think(philo));
}

static int	philo_think(t_philo *philo)
{
	exe_act(philo, THINK);
	take_fork(philo, philo->first);
	take_fork(philo, philo->second);
	return (philo_eat(philo));
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	philo_think(philo);
	return NULL;
}
