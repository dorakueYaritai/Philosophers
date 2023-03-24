/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_make_log.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/24 23:15:02 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	enqueue_log_msg_to_writer(t_share *share, int id, long sec_milli, int act)
{
	t_list	*new_node;
	char	*philo_act_log_massage;

	if (act == LET_OK || act == LET_INIT || act == LET_TRY_TO_TAKE_FORKS)
	{
		return (SUCCESS);
	}
	else if (act == WRITER_END)
		philo_act_log_massage = strdup("");
	else
		philo_act_log_massage = make_msg(id, sec_milli, act, NONE);
	if (philo_act_log_massage == NULL)
	{
		return (ERROR);
	}
	new_node = ft_lstnew(philo_act_log_massage);
	if (new_node == NULL)
	{
		return (ERROR);
	}
	ft_pthread_mutex_lock(&share->queue->mutex);
	ft_enqueue(&share->queue->list, new_node);
	ft_pthread_mutex_unlock(&share->queue->mutex);
	return (SUCCESS);
}

char	*make_prefix_msg(int id, long sec_milli, int act)
{
	char	*join;
	char	*id_str;
	char	*sec_milli_str;
	char	*tmp;

	sec_milli_str = ft_ltoa(sec_milli);
	if (sec_milli_str == NULL)
	{
		return (NULL);
	}
	join = ft_strjoin(sec_milli_str, " ");
	free (sec_milli_str);
	if (join == NULL)
	{
		return (NULL);
	}
	id_str = ft_itoa(id);
	if (id_str == NULL)
	{
		return (NULL);
	}
	tmp = ft_strjoin(join, id_str);
	free (id_str);
	if (tmp == NULL)
	{
		return (NULL);
	}
	free (join);
	return (tmp);
}

char	*make_msg(int id, long sec_milli, int act, int fork_id)
{
	char	*join;
	char	*tmp;

	join = make_prefix_msg(id, sec_milli, act);
	if (join == NULL)
	{
		return (NULL);
	}
	if (act == LET_TAKE_A_FORK)
		tmp = ft_strjoin(join, MSG_FORK);
	else if (act == LET_EAT)
		tmp = ft_strjoin(join, MSG_EAT);
	else if (act == LET_THINK)
		tmp = ft_strjoin(join, MSG_THINK);
	else if (act == LET_SLEEP)
		tmp = ft_strjoin(join, MSG_SLEEP);
	else if (act == LET_DEAD)
		tmp = ft_strjoin(join, MSG_DEAD);
	free (join);
	if (tmp == NULL)
	{
		return (NULL);
	}
	return (tmp);
}

int	print_time(int id, long sec_milli, int act, int fork_id)
{
	static char	*remain;
	static int	remain_count;
	char	*out_put;
	char	*tmp;

	out_put = make_msg(id, sec_milli, act, fork_id);
	if (out_put == NULL)
		return (ERROR);
	if (write(1, out_put, ft_strlen(out_put)) == -1)
		return (ERROR);
	free (out_put);
	if (act == LET_DEAD)
		return (ERROR);
	return (SUCCESS);
}


// void	print_time_printf(int id, long sec_milli, int act, int fork_id)
// {
// 	if (act == LET_TAKE_A_FORK)
// 		printf("%ld %d has taken a fork\n", sec_milli, id);
// 	else if (act == LET_EAT)
// 		printf("%ld %d is eating\n",  sec_milli, id);
// 	else if (act == LET_THINK)
// 		printf("%ld %d is thinking\n",  sec_milli, id);
// 	else if (act == LET_SLEEP)
// 		printf("%ld %d is sleeping\n",  sec_milli, id);
// 	else if (act == LET_DEAD)
// 		printf("%ld %d died\n", sec_milli, id);
// }

// int	print_time(int id, long sec_milli, int act, int fork_id)
// {
// 	static char	*remain;
// 	static int	remain_count;
// 	char	*out_put;
// 	char	*tmp;

// 	out_put = make_msg(id, sec_milli, act, fork_id);
// 	if (out_put == NULL)
// 		return (ERROR);
// 	if (remain_count == 0)
// 	{
// 		remain = out_put;
// 		remain_count++;
// 	}
// 	else if (remain_count < 10)
// 	{
// 		tmp = ft_strjoin(remain, out_put);
// 		if (tmp == NULL)
// 			return (ERROR);
// 		free (remain);
// 		remain = tmp;
// 		remain_count++;
// 	}
// 	if (remain_count == 10)
// 	{
// 		if (write(1, remain, ft_strlen(remain)) == -1)
// 			return (ERROR);
// 		remain_count = 0;
// 	}

// 	if (write(1, out_put, ft_strlen(out_put)) == -1)
// 		return (ERROR);
// 	free (out_put);
// 	if (act == LET_DEAD)
// 		return (ERROR);
// 	return (SUCCESS);
// }

