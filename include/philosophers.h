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
#include <errno.h>

typedef struct s_fork t_fork;
struct s_fork{
	bool			is_fork_available;
	pthread_mutex_t	fork_check;
	pthread_mutex_t	fork;
	int	fork_id;
};

typedef struct s_dead t_dead;
struct s_dead{
	bool			is_death;
	pthread_mutex_t	is_death_mutex;
};

typedef struct s_philo t_philo;
struct s_philo{
	time_t	time_to_starve;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	time_to_die;
	int		philo_id;
	bool	is_death;
	pthread_mutex_t	*is_death_mutex;
	t_fork			*first;
	t_fork			*second;
};
// bool	does_want_eat;

typedef struct s_waiter t_waiter;
struct s_waiter{
	size_t			philonum;
	time_t			*time_to_die;
	pthread_mutex_t	*forks;

	bool	*isdeath;
};

#define FORK 0
#define EAT 1
#define THINK 2
#define DEAD 3
#define SLEEP 4
#define NONE 0
#define SUCCESS 0
#define ERROR 1

// parse.c
int			parse_argment(int argc, char *argv[]);
// init.c
t_philo		*init_philo(char *argv[], t_fork *m_forks);
// t_dead	*init_t_dead(char *philonum);
// t_fork		*init_fork(char *philonum);
t_dead	*init_t_dead(int philonum);
t_fork	*init_fork(int philo_num);
pthread_t	*init_th_id(char *argv[]);
void		print_philo_status(t_philo *philo);

// routine.c
void*		 routine(void *philo);

// routine_utils.c
int			print_time(int id, long sec_milli, int act, int fork_id);
bool	check_am_i_dead(t_philo *philo);
// int			check_am_i_dead(t_philo *philo);

// routine_fork.c
int			take_fork(t_philo *philo, t_fork *fork);
int			put_fork(t_philo *philo, t_fork *fork);

// libft
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_itoa(int n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_ltoa(long n);

#endif