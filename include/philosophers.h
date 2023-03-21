/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:53:14 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 08:12:27 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
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
#include <limits.h>

typedef struct s_list t_list;
struct s_list{
	void	*content;
	t_list	*next;
};

typedef struct s_shared_resourse t_shared_resourse;
struct s_shared_resourse{
	bool			is_available;
	pthread_mutex_t	is_available_mutex;
	pthread_mutex_t	stuff;
};

typedef struct s_fork t_fork;
struct s_fork{
	t_shared_resourse	fork;
	time_t				*time_to_die[2];
	int					fork_id;
};

typedef struct s_dead t_dead;
struct s_dead{
	t_shared_resourse	mutex;
	time_t				*time_to_die;
	int					*must_eat_times;
	// bool				is_death;
};

typedef struct s_wish t_wish;
struct s_wish{
	t_shared_resourse	mutex;
	int					let_me_eat;
	long				sec_milli;
	int					fork_id;
};

typedef struct s_share t_share;
struct s_share{
	t_wish				*wishs;
	t_dead				*dead_info;
	t_fork				*forks;
	time_t				time_to_starve;
	time_t				*philos_time_to_dead;
	int					*philos_eat_times;
	int					must_eat_times;
	// time_t				time_to_assume_starve;
	long				philo_num;
	bool				must_eat_times_exists;
	pthread_t			*th_id;
};

typedef struct s_status t_status;
struct s_status{
	time_t			time_to_starve;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	int				must_eat_times;
};

typedef struct s_philo t_philo;
struct s_philo{
	int				philo_id;
	t_status		status;
	t_fork			*forks[2];
	t_dead			*dead_info;
	t_wish			*wish;
};


enum {
	LET_TRY_TO_TAKE_FORKS,
	LET_TAKE_A_FORK,
	LET_PUT_OFF_A_FORK,
	LET_EAT,
	LET_THINK,
	LET_DEAD,
	LET_SLEEP,
	LET_THANK_YOU,
	LET_OK,
	LET_YOU_ARE_ALREADY_DEAD,
	LET_REJECT,
	LET_INIT,
};

#define MSG_FORK " has taken a fork\n"
#define MSG_EAT " is eating\n"
#define MSG_THINK " is thinking\n"
#define MSG_SLEEP " is sleeping\n"
#define MSG_DEAD " died\n"

#define FINISH 2
#define NONE 0
#define SUCCESS 0
#define ERROR 1
#define FIRST 0
#define SECOND 1
#define FULL 0
#define HUNGRY 1
#define CALLING_FOR_AMBULANCE 2
#define SITTING_ON_A_COFFIN 2

#define ERR_INVALID_ARG 1
#define ERR_ARG_NUM 2

// parse.c
int			parse_argment(int argc, char *argv[]);

// monitor.c
int monitor_philos_death(t_share *share);

// monitor_fork.c
int	is_ok_the_guy_eat(t_share *share,int id, int num);
void	ultra_debug(int id, int left_id, int right_id, t_dead *dead_info);
bool	guys_forks_avilable(t_share *share, int left_id, int right_id, int num);
// bool	guys_forks_avilable(t_share *share, int id, int num);

// init.c
t_philo	*init_philos(t_status *status, t_share *share);
// t_philo	*init_philos(t_status *status, t_fork *m_forks, t_share *share);
// t_philo	*init_philos(t_status *status, t_share *share);

// init_other.c
int			init_share(t_share *share, t_status *status, char *philo_num_arg);
pthread_t	*init_th_id(int philo_num);
t_wish		*init_wishs(int philo_num);
t_dead		*init_t_dead(int philo_num);
t_fork		*init_fork(int philo_num);
int			init_shared_resourse(t_shared_resourse	*resourse);
int	init_status(t_status *status, char **argv, int argc);

// routine.c
int			philo_think(t_philo *philo);
int			exe_act(t_philo *philo, int act);

// routine_init.c
void* routine_init(void *_philo);

// routine_utils.c
int			print_time(int id, long sec_milli, int act, int fork_id);
bool		check_am_i_dead(t_philo *philo);

// routine_fork.c
int			take_forks(t_philo *philo);
int			put_forks(t_philo *philo);
int	is_ok_the_guy_eat(t_share *share,int id, int num);
int	is_ok_the_guy_eat2(t_share *share,int id, int num);

// wish.c
// int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id);
int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id, int id);
// int	is_wish_come(t_wish *wish);
int		is_wish_come(t_wish *wish, int id);
int		thanks_a_host(t_wish *wish);

int			ft_pthread_mutex_trylock(t_shared_resourse *sourse);
int			ft_pthread_mutex_unlock(t_shared_resourse *sourse);
int			ft_pthread_mutex_lock(t_shared_resourse *sourse);

#endif