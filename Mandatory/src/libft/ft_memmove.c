/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:25:16 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/30 20:54:46 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	*ft_normal_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ucp_dst;
	const unsigned char	*ucp_src;

	ucp_dst = (unsigned char *)dst;
	ucp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ucp_dst[i] = ucp_src[i];
		i++;
	}
	return (dst);
}

static void	*ft_reverse_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	size_t				j;
	unsigned char		*ucp_dst;
	const unsigned char	*ucp_src;

	ucp_dst = (unsigned char *)dst;
	ucp_src = (const unsigned char *)src;
	i = 0;
	j = n - 1;
	while (i < n)
	{
		ucp_dst[j] = ucp_src[j];
		j--;
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == NULL)
		return (NULL);
	if (dst == src || len == 0)
		return (dst);
	else if (dst < src)
		return (ft_normal_memcpy(dst, src, len));
	else if (src < dst)
		return (ft_reverse_memcpy(dst, src, len));
	else
		return (dst);
}
