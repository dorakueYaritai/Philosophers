/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 06:31:52 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

char	*make_prefix_msg(int id, long sec_milli, int act)
{
	char	*join;
	char	*id_str;
	char	*sec_milli_str;

	id_str = ft_itoa(id);
	if (id_str == NULL)
		return (NULL);
	sec_milli_str = ft_ltoa(sec_milli);
	if (sec_milli_str == NULL)
		return (NULL);
	join = ft_strjoin(sec_milli_str, " ");
	free (sec_milli_str);
	if (join == NULL)
	{
		free (id_str);
		return (NULL);
	}
	join = ft_strjoin(join, id_str);
	free (id_str);
	if (join == NULL)
		return (NULL);
	return (join);
}

char	*make_msg(int id, long sec_milli, int act, int fork_id)
{
	char	*join;

	join = make_prefix_msg(id, sec_milli, act);
	if (act == LET_TAKE_A_FORK)
		join = ft_strjoin(join, MSG_FORK);
	else if (act == LET_EAT)
		join = ft_strjoin(join, MSG_EAT);
	else if (act == LET_THINK)
		join = ft_strjoin(join, MSG_THINK);
	else if (act == LET_SLEEP)
		join = ft_strjoin(join, MSG_SLEEP);
	else if (act == LET_DEAD)
		join = ft_strjoin(join, MSG_DEAD);
	if (join == NULL)
		return (NULL);
	return (join);
}

int	print_time(int id, long sec_milli, int act, int fork_id)
{
	static char	*remain;
	static int	remain_count;
	char	*out_put;
	char	*tmp;

	out_put = make_msg(id, sec_milli, act, fork_id);
	// if (out_put == NULL)
	// 	return (ERROR);
	// if (remain_count == 0)
	// 	remain = out_put;
	// else if (remain_count < 10)
	// {
	// 	tmp = ft_strjoin(remain, out_put);
	// 	if (tmp == NULL)
	// 		return (ERROR);
	// 	free (remain);
	// 	remain = tmp;
	// 	remain_count++;
	// }
	// if (remain_count == 10)
	// {
	// 	if (write(1, remain, ft_strlen(remain)) == -1)
	// 		return (ERROR);
	// 	remain_count = 0;
	// }
	if (write(1, out_put, ft_strlen(out_put)) == -1)
		return (ERROR);
	free (out_put);
	if (act == LET_DEAD)
		return (ERROR);
	return (SUCCESS);
}

// int	print_time(int id, long sec_milli, int act, int fork_id)
// {
// 	char	*sec_milli_str;
// 	char	*id_str;
// 	char	*join;

// 	id_str = ft_itoa(id);
// 	sec_milli_str = ft_ltoa(sec_milli);
// 	join = ft_strjoin(sec_milli_str, " ");
// 	join = ft_strjoin(join, id_str);

// 	if (act == LET_TAKE_A_FORK)
// 	{
// 		// join = ft_strjoin(join, " has taken	a fork ");
// 		// join = ft_strjoin(join, ft_ltoa(fork_id));
// 		// join = ft_strjoin(join, "\n");
// 		join = ft_strjoin(join, " has taken a fork\n");
// 	}
// 	else if (act == LET_EAT)
// 		join = ft_strjoin(join, " is eating\n");
// 	else if (act == LET_THINK)
// 		join = ft_strjoin(join, " is thinking\n");
// 	else if (act == LET_SLEEP)
// 		join = ft_strjoin(join, " is sleeping\n");
// 	else if (act == LET_DEAD)
// 	{
// 		join = ft_strjoin(join, " died\n");
// 		if (write(1, join, strlen(join)) == -1)
// 			return (ERROR);
// 		return (SUCCESS);
// 	}
// 	else if (act == LET_PUT_OFF_A_FORK)
// 	{
// 		join = "";
// 		// join = ft_strjoin(join, " has putoff a	fork ");
// 		// join = ft_strjoin(join, ft_ltoa(fork_id));
// 		// join = ft_strjoin(join, "\n");
// 	}
// 	if (write(1, join, strlen(join)) == -1)
// 		return (ERROR);
// 	return (SUCCESS);
// }

void	print_time_printf(int id, long sec_milli, int act, int fork_id)
{
	if (act == LET_TAKE_A_FORK)
		printf("%ld %d has taken a fork\n", sec_milli, id);
	else if (act == LET_EAT)
		printf("%ld %d is eating\n",  sec_milli, id);
	else if (act == LET_THINK)
		printf("%ld %d is thinking\n",  sec_milli, id);
	else if (act == LET_SLEEP)
		printf("%ld %d is sleeping\n",  sec_milli, id);
	else if (act == LET_DEAD)
		printf("%ld %d died\n", sec_milli, id);
}
