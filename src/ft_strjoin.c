/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:27:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/20 10:00:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_cpy;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p_cpy = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (p_cpy == NULL)
		return (NULL);
	ft_strlcpy(p_cpy, s1, len_s1 + 1);
	ft_strlcat(p_cpy, s2, len_s1 + len_s2 + 1);
	return (p_cpy);
}
