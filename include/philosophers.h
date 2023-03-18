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

typedef struct s_philo t_philo;
struct s_philo{
	time_t	time_to_starve;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	time_to_die;
	int		philo_id;
	int		philo_num;
	bool	does_want_eat;
	bool	is_death;
	bool	is_eating;
	bool	is_sleeping;
	bool	is_thinking;
	bool	*is_fork_available_lh;
	bool	*is_fork_available_rh;
	pthread_mutex_t	*fork_check_lh;
	pthread_mutex_t	*fork_check_rh;
	t_fork			*forks;
	// pthread_mutex_t	*forks;
	pthread_mutex_t	*fork_lh;
	pthread_mutex_t	*fork_rh;
	pthread_mutex_t	*death_check;
	int	fork1_id;
	int	fork2_id;
	t_fork			*first;
	t_fork			*second;
};

typedef struct s_waiter t_waiter;
struct s_waiter{
	size_t			philonum;
	time_t			*time_to_die;
	pthread_mutex_t	*forks;

	bool	*isdeath;
};

t_philo	*init_philo(char *argv[], t_fork *m_forks);
pthread_t	*init_th_id(char *argv[]);
// pthread_mutex_t	*init_fork(char *philonum);
t_fork	*init_fork(char *philonum);
bool	*init_is_fork_available(char *philonum);
void	print_philo_status(t_philo *philo);
void* routine(void *philo);
int	parse_argment(int argc, char *argv[]);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_itoa(int n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_ltoa(long n);


#endif