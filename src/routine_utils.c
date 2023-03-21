/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/21 18:34:31 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	print_time(int id, long sec_milli, int act, int fork_id)
{
	char	*sec_milli_str;
	char	*id_str;
	char	*join;

	id_str = ft_itoa(id);
	sec_milli_str = ft_ltoa(sec_milli);
	join = ft_strjoin(sec_milli_str, " ");
	join = ft_strjoin(join, id_str);

	if (act == LET_TAKE_A_FORK)
	{
		// join = ft_strjoin(join, " has taken	a fork ");
		// join = ft_strjoin(join, ft_ltoa(fork_id));
		// join = ft_strjoin(join, "\n");
		join = ft_strjoin(join, " has taken a fork\n");
	}
	else if (act == LET_EAT)
		join = ft_strjoin(join, " is eating\n");
	else if (act == LET_THINK)
		join = ft_strjoin(join, " is thinking\n");
	else if (act == LET_SLEEP)
		join = ft_strjoin(join, " is sleeping\n");
	else if (act == LET_DEAD)
	{
		join = ft_strjoin(join, " died\n");
		if (write(1, join, strlen(join)) == -1)
			return (ERROR);
		return (SUCCESS);
	}
	else if (act == LET_PUT_OFF_A_FORK)
	{
		join = "";
		// join = ft_strjoin(join, " has putoff a	fork ");
		// join = ft_strjoin(join, ft_ltoa(fork_id));
		// join = ft_strjoin(join, "\n");
	}
	if (write(1, join, strlen(join)) == -1)
		return (ERROR);
	return (SUCCESS);
}

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
