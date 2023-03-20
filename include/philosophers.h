/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:53:14 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 14:19:31 by kakiba           ###   ########.fr       */
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
	long				sec_milli;
	int					fork_id;
};

typedef struct s_status t_status;
struct s_status{
	time_t			time_to_starve;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	int				must_eat_times;
};

// typedef struct s_philo t_philo;
// struct s_philo{
// 	int				philo_id;
// 	t_status		status;
// 	t_fork			*forks[2];
// 	t_dead			*dead_info;
// 	t_wish			*wish;
// };

typedef struct s_philo t_philo;
struct s_philo{
	int				philo_id;
	int				requtest_id;
	t_status		status;
	// int				must_eat_times;
	// time_t			time_to_starve;
	// time_t			time_to_eat;
	// time_t			time_to_sleep;
	// time_t			time_to_die;
	t_fork			*forks[2];
	t_dead			*dead_info;
	t_wish			*wish;
};

typedef struct s_shere t_shere;
struct s_shere{
	t_wish				*wishs;
	t_dead				*dead_info;
	t_fork				*forks;
	long				philo_num;
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
};


#define FORK 0
#define EAT 1
#define THINK 2
#define DEAD 3
#define SLEEP 4
#define PUTOFF 5
#define THANK_U 6
#define PLEASE 7
#define OK 8
#define U_ARE_ALREADY_DEAD 9
// #define DEAD 10
#define REJECT 11

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
int monitor_philos_death(t_shere *shere);
// bool	guys_forks_avilable(t_fork *forks, int id, int num);
bool	guys_forks_avilable(t_shere *shere, int id, int num);

// init.c
t_philo	*init_philos(t_status *status, t_shere *shere);
// t_philo	*init_philos(t_status *status, t_fork *m_forks, t_shere *shere);
// t_philo	*init_philos(t_status *status, t_shere *shere);

// init_other.c
pthread_t	*init_th_id(int philo_num);
t_wish		*init_wishs(int philo_num);
t_dead		*init_t_dead(int philo_num);
t_fork		*init_fork(int philo_num);
int			init_shered_resourse(t_shered_resourse	*resourse);
int			init_status(t_status *status, char **argv, int argc);

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
// int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id);
int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id, int id);
// int	is_wish_come(t_wish *wish);
int	is_wish_come(t_wish *wish, int id);
int		thanks_a_host(t_wish *wish);

int			ft_pthread_mutex_trylock(t_shered_resourse *sourse);
int			ft_pthread_mutex_unlock(t_shered_resourse *sourse);
int			ft_pthread_mutex_lock(t_shered_resourse *sourse);

#endif