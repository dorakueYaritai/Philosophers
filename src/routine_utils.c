/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:37:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 16:26:03 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_time_printf(int id, long sec_milli, int act, int fork_id)
{
	if (act == FORK)
		printf("%ld %d has taken a fork\n", sec_milli, id);
	else if (act == EAT)
		printf("%ld %d is eating\n",  sec_milli, id);
	else if (act == THINK)
		printf("%ld %d is thinking\n",  sec_milli, id);
	else if (act == SLEEP)
		printf("%ld %d is sleeping\n",  sec_milli, id);
	else if (act == DEAD)
		printf("%ld %d died\n", sec_milli, id);
}
