/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:12:15 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 23:13:09 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_msleep(long sleep_time)
{
	const long	now_time = ft_get_time_in_millisec();
	const long	goal_time = now_time + sleep_time;

	if (now_time == -1)
		return (-1);
	while (goal_time > ft_get_time_in_millisec())
		;
	return (0);
}
