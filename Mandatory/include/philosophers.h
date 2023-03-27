/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:53:14 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 09:19:50 by kakiba           ###   ########.fr       */
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

typedef struct s_queue t_queue;
struct s_queue{
	t_shared_resourse	mutex;
	t_list				*list;
	bool				do_proceed;
};

typedef struct s_wish_info t_wish_info;
struct s_wish_info{
	int					request;
	long				act_time;
	int					fork_id;
};

typedef struct s_wish t_wish;
struct s_wish{
	t_shared_resourse	mutex;
	t_wish_info			request_info;
	int					request;
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

typedef struct s_share t_share;
struct s_share{
	t_wish				*wishs;
	t_fork				*forks;
	time_t				time_to_starve;
	time_t				*philos_time_to_dead;
	int					*philos_eat_times;
	int					must_eat_times;
	// time_t				time_to_assume_starve;
	long				philo_num;
	bool				must_eat_times_exists;
	pthread_t			*th_id;
	t_queue				*queue;
	// t_list				*msg_quere;
};

typedef struct s_a_share t_a_share;
struct s_a_share{
	t_wish				*wish;
	t_status			status;
	t_queue				*queue;
	bool				must_eat_times_exists;
	long				philo_num;
	int					philo_id;
	int					philos_eat_times;
	time_t				philos_time_to_dead;
};

typedef struct s_philo t_philo;
struct s_philo{
	int				philo_id;
	t_status		status;
	t_fork			*forks[2];
	t_wish			*wish;
};

enum {
	LET_EAT,
	LET_THINK,
	LET_SLEEP,
	LET_TRY_TO_TAKE_FORKS,
	LET_TAKE_A_FORK,
	LET_DEAD,
	LET_OK,
	LET_INIT,
	WRITER_END,
};

#define MSG_FORK " has taken a fork\n"
#define MSG_EAT " is eating\n"
#define MSG_THINK " is thinking\n"
#define MSG_SLEEP " is sleeping\n"
#define MSG_DEAD " died\n"

#define SUCCESS 0
#define ERROR 1
#define FOUND_DEAD 2

#define FIRST 0
#define SECOND 1

#define FINISH 2
#define NONE 0

#define ERR_INVALID_ARG 1
#define ERR_ARG_NUM 2

int		monitor_create(t_share *share, int monitor_id);
void	*monitor_init(void *share);

// parse.c
int			parse_argment(int argc, char *argv[]);

// monitor.c
int monitor_philos(t_share *share);

// monitor_fork.c
int	is_ok_the_guy_take_forks(t_share *share,int own_id, int num);
void	ultra_debug(int id, int left_id, int right_id);
bool	guys_forks_avilable(t_share *share, int left_id, int right_id, int num);

// monitor_death
int		answer_dead_to_all_request(t_share *share);
bool	did_the_old_man_go_heaven(t_share *share, int id);

// monitor_utils
bool		is_must_eat_times_fulfilled(t_share *share);
int			enqueue_log_msg_to_writer(t_share *share, \
	int id, long sec_milli, int act);

// init.c
t_philo	*init_philos(t_status *status, t_share *share);

int	ft_return(t_philo *philo, int ret);
void	init_wish_info(t_wish_info *info, long act_time, int fork_id, int request);

// init_other.c
int			init_share(t_share *share, t_status *status, char *philo_num_arg);
pthread_t	*init_th_id(int philo_num);
t_wish		*init_wishs(int philo_num);
t_fork		*init_fork(int philo_num);
int			init_shared_resourse(t_shared_resourse	*resourse);
int	init_status(t_status *status, char **argv, int argc);

// routine.c
// int			philo_think(t_philo *philo);
int			exe_act(t_philo *philo, int act);

// routine_init.c
void* routine_init(void *_philo);

// routine_utils.c
int	print_time(int id, long sec_milli, int act);
bool		check_am_i_dead(t_philo *philo);
int	enqueue_log_msg_to_writer(t_share *share, int id, long sec_milli, int act);
t_list	*ft_lstnew(void *content);

// thread.c
int	threads_create(t_philo *philos, pthread_t *th_id, int philo_num);
int	writer_create(t_queue *queue, pthread_t *th_id, int writer_id);
int	threads_join(pthread_t *th_id, int thread_num);


// routine_fork.c
int			take_forks(t_philo *philo);
int			put_forks(t_philo *philo);
int	is_ok_the_guy_eat(t_share *share,int id, int num);
int	is_ok_the_guy_eat2(t_share *share,int id, int num);

// wish.c
// int	update_wish_status(t_wish *wish, int request, long sec_milli, int fork_id);
int	update_wish_status(t_wish *wish, t_wish_info *info);
// int	get_monitor_answer(t_wish *wish);
int		get_monitor_answer(t_wish *wish);
int		thanks_a_host(t_wish *wish);

int			ft_pthread_mutex_trylock(t_shared_resourse *sourse);
int			ft_pthread_mutex_unlock(t_shared_resourse *sourse);
int			ft_pthread_mutex_lock(t_shared_resourse *sourse);
void	ft_enqueue(t_list **lst, t_list *new);
t_list	*ft_dequeue(t_list **lst);
int		print_que(t_queue *queue);
void	*writer_init(void *arg);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstlast(t_list *lst);

#endif
