/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 04:00:55 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/17 10:56:09 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

//static size_t	ft_strlen_s(const char *s)
//{
//	size_t	len;

//	len = 0;
//	if (s == NULL)
//		return (0);
//	while (s[len] != '\0')
//		len++;
//	return (len);
//}

//size_t	ft_strlen(const char *s)
//{
//	return (ft_strlen_s(s));
//}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

/*
int main()
{
	size_t n = UINT_MAX;
	char *str = malloc(sizeof(char) * (n + 11));
	memset(str, 'a', n);
	str[n] = '\0';
	printf("%zu\n", ft_strlen(str));

	n += 10;
	memset(str + UINT_MAX, 'a', 10);
	str[n] = '\0';
	printf("%zu\n", ft_strlen(str));

	printf("%zu\n", ft_strlen(NULL));
	printf("%zu\n", ft_strlen("\0"));
	printf("%zu\n", ft_strlen("abc"));

	system("leaks -q a.out");
	return (0);
}
*/
