/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:27:40 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/20 10:00:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ucp_b;
	unsigned char	uc_c;
	size_t			i;

	ucp_b = (unsigned char *)b;
	uc_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ucp_b[i] = uc_c;
		i++;
	}
	return (b);
}
