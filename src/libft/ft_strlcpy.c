/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:56:41 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/20 10:00:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	if (dst == NULL)
		return (0);
	len_src = ft_strlen_s(src);
	if (len_src < dstsize)
		ft_memmove(dst, src, len_src + 1);
	else if (0 < dstsize)
	{
		ft_memmove(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len_src);
}

/*
   int main()
   {
   char	*st_dest;
   char	*ft_dest;
   char	*str;
   size_t	n;

   str = strdup("ab");

   n = -1;
   st_dest = strdup("");
   ft_dest = strdup("");
   strlcpy(st_dest, str, n);
   printf("st:%s,n=%zu\n", st_dest, n);
   ft_strlcpy(ft_dest, str, n);
   printf("ft:%s,n=%zu\n", ft_dest, n);

   n = 0;
   while (n < 5)
   {
   st_dest = strdup(""); ft_dest = strdup("");
   strlcpy(st_dest, str, n);		printf("st:%s,n=%zu\n", st_dest, n);
   ft_strlcpy(ft_dest, str, n);		printf("ft:%s,n=%zu\n", ft_dest, n);
   n++;
   }

   n = 0; st_dest = strdup(""); ft_dest = strdup("");
   printf("%s\n", st_dest);
   strlcpy(st_dest, str, n);	printf("st:%s,n=%zu\n", st_dest, n);
   ft_strlcpy(ft_dest, str, n);	printf("ft:%s,n=%zu\n", ft_dest, n);
   }
   */
