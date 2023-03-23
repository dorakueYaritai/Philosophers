/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:29:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 17:29:53 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

bool	is_must_eat_times_fulfilled(t_share *share)
{
	int	i;

	i = 0;
	if (share->must_eat_times_exists == false)
		return (false);
	while (i < share->philo_num)
	{
		if (share->philos_eat_times[i] < share->must_eat_times)
			return (false);
		i++;
	}
	return (true);
}

int	enqueue_log_msg_to_writer(t_share *share, int id, long sec_milli, int act)
{
	t_list	*new_node;
	char	*philo_act_log_massage;

	if (act == WRITER_END)
		philo_act_log_massage = strdup("");
	else
		philo_act_log_massage = make_msg(id, sec_milli, act, NONE);
	if (philo_act_log_massage == NULL)
		return (ERROR);
	new_node = ft_lstnew(philo_act_log_massage);
	if (new_node == NULL)
		return (ERROR);
	ft_pthread_mutex_lock(&share->queue->mutex);
	ft_enqueue(&share->queue->list, new_node);
	ft_pthread_mutex_unlock(&share->queue->mutex);
	return (0);
}
