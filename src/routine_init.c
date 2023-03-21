/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:36:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/22 05:44:03 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

static void	birth_philo_baby(t_philo *philo)
{
	struct timeval t1;
	long sec_milli;

	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_time_to_die(philo, sec_milli + philo->status.time_to_starve);
	// update_time_to_die(philo, sec_milli + philo->time_to_starve);
}

void* routine_init(void *philo){
	t_philo			*_philo;
	struct timeval	t1;
	long			sec_milli;

	_philo = (t_philo *)philo;
	gettimeofday(&t1, NULL);
	sec_milli = (long)(t1.tv_sec) * 1000 + (long)(t1.tv_usec) / 1000;
	update_wish_status(_philo->wish, LET_INIT, sec_milli, NONE, _philo->philo_id);

	// exe_act(_philo, LET_INIT);

	// birth_philo_baby(_philo);

	if (philo_think(_philo))
		return (NULL);
	return (NULL);
		// char	*join;
		// join = ft_strjoin("", ft_ltoa(_philo->philo_id));
		// join = ft_strjoin(join, ": I am dead!\n");
		// write(1, join, ft_strlen(join));

}
