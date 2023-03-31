/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_make_log.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 21:29:57 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static char	*make_prefix_msg(int id, long sec_milli);
static char	*make_msg(int id, long sec_milli, int act);
static int	is_log_needed_action(int act);

int	enqueue_log_msg_to_writer(t_share *share, int id, long sec_milli, int act)
{
	t_list	*new_node;
	char	*philo_act_log_massage;

	if (is_log_needed_action(act) == false)
		return (SUCCESS);
	philo_act_log_massage = make_msg(id, sec_milli, act);
	if (philo_act_log_massage == NULL)
		return (ERROR);
	new_node = ft_lstnew(philo_act_log_massage);
	if (new_node == NULL)
		return (ERROR);
	ft_pthread_mutex_lock(&share->queue->mutex);
	if (share->queue->do_proceed)
		ft_enqueue(&share->queue->list, new_node);
	else
	{
		free (philo_act_log_massage);
		free (new_node);
		ft_pthread_mutex_unlock(&share->queue->mutex);
		return (ERROR);
	}
	if (act == LET_DEAD)
		share->queue->do_proceed = false;
	ft_pthread_mutex_unlock(&share->queue->mutex);
	return (SUCCESS);
}

static char	*make_prefix_msg(int id, long sec_milli)
{
	char	*join;
	char	*id_str;
	char	*sec_milli_str;
	char	*tmp;

	sec_milli_str = ft_ltoa(sec_milli);
	if (sec_milli_str == NULL)
		return (NULL);
	join = ft_strjoin(sec_milli_str, " ");
	free (sec_milli_str);
	if (join == NULL)
		return (NULL);
	id_str = ft_itoa(id);
	if (id_str == NULL)
		return (NULL);
	tmp = ft_strjoin(join, id_str);
	free (id_str);
	if (tmp == NULL)
		return (NULL);
	free (join);
	return (tmp);
}

static char	*make_msg(int id, long sec_milli, int act)
{
	char	*join;
	char	*tmp;

	tmp = NULL;
	join = make_prefix_msg(id, sec_milli);
	if (join == NULL)
		return (NULL);
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
		return (NULL);
	return (tmp);
}

static int	is_log_needed_action(int act)
{
	return (act == LET_EAT || act == LET_TAKE_A_FORK \
	|| act == LET_SLEEP || act == LET_DEAD || act == LET_THINK);
}
