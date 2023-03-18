#include <philosophers.h>
#include <stdlib.h>

static int	philo_sleep(t_philo *philo);
static int	philo_think(t_philo *philo);
static int	philo_eat(t_philo *philo);	

#define FORK 0
#define EAT 1
#define THINK 2
#define DEAD 3
#define SLEEP 4

void	print_time(int id, long sec_milli, int act, int fork_id)
{
	char	*sec_milli_str;
	char	*id_str;
	char	*join;

	id_str = ft_itoa(id);
	sec_milli_str = ft_ltoa(sec_milli);
	join = ft_strjoin(sec_milli_str, " ");
	join = ft_strjoin(join, id_str);

	// if (act == FORK)
	// 	printf("%ld %d has taken a fork\n", sec_milli, id);
	// else if (act == EAT)
	// 	printf("%ld %d is eating\n",  sec_milli, id);
	// else if (act == THINK)
	// 	printf("%ld %d is thinking\n",  sec_milli, id);
	// else if (act == SLEEP)
	// 	printf("%ld %d is sleeping\n",  sec_milli, id);
	// else
	// 	printf("%ld %d died\n", sec_milli, id);
	if (act == FORK)
	{
		join = ft_strjoin(join, " has taken a fork ");
		join = ft_strjoin(join, ft_itoa(fork_id));
		join = ft_strjoin(join, "\n");
		// join = ft_strjoin(join, " has taken a fork \n");
	}
	else if (act == EAT)
		join = ft_strjoin(join, " is eating\n");
	else if (act == THINK)
		join = ft_strjoin(join, " is thinking\n");
	else if (act == SLEEP)
		join = ft_strjoin(join, " is sleeping\n");
	else
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			exit (1);
		exit (1);
	}
	if (write(1, join, strlen(join)) == -1)
		exit(1);
}

// void	take_fork(t_philo *philo, pthread_mutex_t *fork, int fork_id)
// {
// 	struct timeval t1;
// 	long sec_milli;

// 	pthread_mutex_lock(fork);
// 	gettimeofday(&t1, NULL);
// 	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
// 	print_time(philo->philo_id, sec_milli, FORK, fork_id);
// }

void	take_fork(t_philo *philo, t_fork *fork)
{
	struct timeval t1;
	long sec_milli;

	pthread_mutex_lock(&fork->fork);
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	print_time(philo->philo_id, sec_milli, FORK, fork->fork_id);
}

void	put_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_unlock(&fork->fork);
}

int	check_am_i_dead(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		print_time(philo->philo_id, philo->time_to_die, DEAD, 0);
	}
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die != -1 && philo->time_to_die <= sec_milli)
	{
		print_time(philo->philo_id, philo->time_to_die, DEAD, 0);
	}
	print_time(philo->philo_id, sec_milli, EAT, 0);
	philo->time_to_die = sec_milli + philo->time_to_starve;
	usleep((unsigned int)(philo->time_to_eat) * 1000);
	put_fork(philo, philo->first);
	put_fork(philo, philo->se);
	// pthread_mutex_unlock(philo->fork_lh);
	// pthread_mutex_unlock(philo->fork_rh);
	return (philo_sleep(philo));
}

static int	philo_sleep(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	if (philo->time_to_die <= sec_milli)
	{
		print_time(philo->philo_id, philo->time_to_die, DEAD, 0);
	}
	print_time(philo->philo_id, sec_milli, SLEEP, 0);
	usleep((unsigned int)(philo->time_to_sleep) * 1000);
	return (philo_think(philo));
}

static int	philo_think(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	print_time(philo->philo_id, sec_milli, THINK, 0);
	take_fork(philo, philo->first);
	// take_fork(philo, philo->fork_lh, philo->fork1_id);
	check_am_i_dead(philo);
	take_fork(philo, philo->second);
	// take_fork(philo, philo->fork_rh, philo->fork2_id);
	return (philo_eat(philo));
}

void* routine(void *philo){
	t_philo	*_philo;

	_philo = (t_philo *)philo;
	philo_think(philo);
	return NULL;
}
