/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 22:52:16 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/27 22:52:17 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <philosophers.h>

int	parse_argment(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		return (ERR_ARG_NUM);
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i], 0) == false)
		{
			return (ERR_INVALID_ARG);
		}
		i++;
	}
	return (SUCCESS);
}
