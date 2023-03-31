/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time_in_millisec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:42:30 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 20:58:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	ft_get_time_in_millisec(void)
{
	struct timeval	t1;
	long			sec_milli;
	long			s_time;

	if (gettimeofday(&t1, NULL))
	{
		return (-1);
	}
	s_time = (long)(t1.tv_sec);
	sec_milli = s_time * 1000 + (long)(t1.tv_usec) / 1000;
	return (sec_milli);
}
