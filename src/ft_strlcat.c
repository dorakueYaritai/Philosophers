/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:53:34 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/17 10:50:30 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>


static size_t	ft_strnlen_s(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

static size_t	ft_strlen_s(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	n_len_dst;

	len_src = ft_strlen_s(src);
	len_dst = ft_strlen_s(dst);
	n_len_dst = ft_strnlen_s(dst, dstsize);
	if (dstsize > len_dst)
	{
		if (len_src < dstsize - len_dst)
			ft_strlcpy(dst + len_dst, src, len_src + 1);
		else
			ft_strlcpy(dst + len_dst, src, dstsize - len_dst);
	}
	return (n_len_dst + len_src);
}
/*
   int    main()
   {
   char    dest[30] = "abcde";
   char    ft_dest[30] = "abcde";
   char    *src;

   src = "1234567890123456";
   printf("   strlcat: %s,%lu\n", dest, strlcat(dest, src,20));
   printf("ft_strlcat: %s,%zu\n", ft_dest, ft_strlcat(ft_dest, src, 20));
   }
   */
