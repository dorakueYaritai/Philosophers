/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 08:09:20 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>


void* routine_init(void *_philo){
	t_philo			*philo;
	struct timeval	t1;
	long			sec_milli;
	int				ans;

	philo = (t_philo *)_philo;
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_wish_status(philo->wish, LET_INIT, sec_milli, NONE, philo->philo_id);
	while (1)
	{
		ans = is_wish_come(philo->wish, philo->philo_id);
		if (ans == LET_OK)
			break;
		else if (ans == LET_YOU_ARE_ALREADY_DEAD)
			return (ERROR);
	}
	// exe_act(philo, LET_INIT);

	// birthphilo_baby(philo);

	if (philo_think(philo))
		return (NULL);
	return (NULL);
		// char	*join;
		// join = ft_strjoin("", ft_ltoa(philo->philo_id));
		// join = ft_strjoin(join, ": I am dead!\n");
		// write(1, join, ft_strlen(join));

}
