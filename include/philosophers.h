#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ctype.h>

typedef struct s_philo t_philo;
struct s_philo{
	time_t	time_to_starve;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	time_to_die;
	time_t	start;
	int		philo_id;
	int		philo_num;
	bool	is_death;
	bool	is_eating;
	bool	is_sleeping;
	bool	is_thinking;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*fork_lh;
	pthread_mutex_t	*fork_rh;
};

typedef struct s_waiter t_waiter;
struct s_waiter{
	size_t	philonum;
	time_t	*time_to_die;
	bool	*isdeath;
};


// t_philo	*init_philo(int argc, char *argv[]);
t_philo	*init_philo(char *argv[], pthread_mutex_t	*mutex);
pthread_t	*init_th_id(char *argv[]);
pthread_mutex_t	*init_fork(char *philonum);


#endif