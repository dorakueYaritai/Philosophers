/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time_in_millisec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:42:30 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 17:50:38 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	ft_get_time_in_millisec(void)
{
	struct timeval	t1;
	long			sec_milli;

	if (gettimeofday(&t1, NULL))
	{
		return (-1);
	}
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	return (sec_milli);
}