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


typedef struct s_shered_resourse t_shered_resourse;
struct s_shered_resourse{
	bool			is_available;
	pthread_mutex_t	is_available_mutex;
	pthread_mutex_t	stuff;
};

typedef struct s_fork t_fork;
struct s_fork{
	t_shered_resourse	fork;
	pthread_mutex_t		check_request_status;
	time_t				*time_to_die[2];
	int					fork_id;
};

typedef struct s_dead t_dead;
struct s_dead{
	t_shered_resourse	mutex;
	time_t				*time_to_die;
	bool				is_death;
	// pthread_mutex_t	is_death_mutex;
};

typedef struct s_wish t_wish;
struct s_wish{
	t_shered_resourse	mutex;
	int					let_me_eat;
};

typedef struct s_philo t_philo;
struct s_philo{
	int				philo_id;
	int				requtest_id;
	time_t			time_to_starve;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	t_fork			*forks[2];
	t_dead			*dead_info;
	t_wish			*wish;
	// t_fork			*first;
	// t_fork			*second;
};

typedef struct s_shere t_shere;
struct s_shere{
	t_wish				*wishs;
	t_dead				*dead_info;
	int					philo_num;
};

#define FORK 0
#define EAT 1
#define THINK 2
#define DEAD 3
#define SLEEP 4
#define PUTOFF 5
#define NONE 0
#define SUCCESS 0
#define ERROR 1
#define FIRST 0
#define SECOND 1
#define FULL 0
#define HUNGRY 1
#define CALLING_FOR_AMBULANCE 2
#define SITTING_ON_A_COFFIN 2
#define THANK_YOU 0
#define PLEASE 1
#define OK 2

// parse.c
int			parse_argment(int argc, char *argv[]);

// monitor.c
int monitor_philos_death(t_shere *shere);

// init.c
t_philo	*init_philos(char *argv[], t_fork *m_forks, t_shere *shere);

// init_other.c
pthread_t	*init_th_id(int philo_num);
t_wish		*init_wishs(int philo_num);
t_dead		*init_t_dead(int philo_num);
t_fork		*init_fork(int philo_num);
int			init_shered_resourse(t_shered_resourse	*resourse);

// routine.c
int			update_time_to_die(t_philo *philo, long new_time_to_die);
int			philo_think(t_philo *philo);

// routine_init.c
void*		 routine(void *philo);

// routine_utils.c
int			print_time(int id, long sec_milli, int act, int fork_id);
bool		check_am_i_dead(t_philo *philo);

// routine_fork.c
int			take_forks(t_philo *philo);
int			put_forks(t_philo *philo);

// wish.c
int		update_wish_status(t_wish *wish);
bool	is_wish_come(t_wish *wish);
int		thanks_a_host(t_wish *wish);

// libft
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_itoa(int n);
char		*ft_ltoa(long n);
int			 ft_positive_mod(int dividend, int divisor);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
int			ft_pthread_mutex_trylock(t_shered_resourse *sourse);
int			ft_pthread_mutex_unlock(t_shered_resourse *sourse);
int			ft_pthread_mutex_lock(t_shered_resourse *sourse);

#endif