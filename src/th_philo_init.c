/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/23 18:00:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

void* routine_init(void *_philo){
	t_philo			*philo;
	long			sec_milli;
	int				ans;

	philo = (t_philo *)_philo;
	exe_act(philo, LET_INIT);
	return ((void *) philo_think(philo));
}
