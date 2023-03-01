#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo t_philo;
struct s_philo{
	struct timeval time;
	struct timeval pre_eat_start;
	struct timezone zone;
};



#endif