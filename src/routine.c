#include <philosophers.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);

static int	exe_act(t_philo *philo, int act)
{
	struct timeval t1;
	long sec_milli;
	long time;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (check_am_i_dead(philo))
	{
		return (ERROR);
	}
	if (print_time(philo->philo_id, sec_milli, act, NONE) == ERROR)
		return (ERROR);
	if (act == EAT)
	{
		philo->time_to_die = sec_milli + philo->time_to_starve;
		update_request_status(philo, philo->forks[FIRST], philo->forks[SECOND]);
		usleep((unsigned int)(philo->time_to_eat) * 1000);
	}
	else if (act == SLEEP)
		usleep((unsigned int)(philo->time_to_sleep) * 1000);
	else if (act == THINK)
	{
		// if (sec_milli - philo->time_to_die > philo->time_to_eat + philo->time_to_sleep)
		// 	usleep((unsigned int)(time / 2)* 1000);
		// time = sec_milli - philo->time_to_eat - philo->time_to_sleep - philo->time_to_die;
		// if (time > 0)
		// 	usleep((unsigned int)(time / 5)* 1000);
	}
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	if (exe_act(philo, EAT) == ERROR)
	{
		put_fork(philo, philo->forks[FIRST]);
		put_fork(philo, philo->forks[SECOND]);
		return (ERROR);
	}
	if (put_fork(philo, philo->forks[FIRST]) == ERROR)
		return (ERROR);
	if (put_fork(philo, philo->forks[SECOND]) == ERROR)
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
	if (take_fork(philo,philo->forks[FIRST], NULL) == ERROR)
	{
		return (ERROR);
	}
	if (take_fork(philo, philo->forks[SECOND], philo->forks[FIRST]) == ERROR)
	{
		put_fork(philo, philo->forks[FIRST]);
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
	philo->time_to_die = sec_milli + philo->time_to_starve;
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	birth_philo_baby(philo);
	philo_think(philo);
	return (NULL);
}
