/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:28:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 10:00:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

size_t	ft_get_digit(long n)
{
	long	buf;
	size_t	digit;

	if (n == 0)
		return (1);
	digit = 0;
	buf = n;
	while (buf)
	{
		buf /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_ltoa(long n)
{
	char	*s;
	size_t	digit;
	bool	is_minus;

	is_minus = false;
	digit = ft_get_digit(n);
	if (n < 0)
	{
		digit++;
		is_minus = true;
	}
	s = ft_calloc(1, digit + 1);
	if (s == NULL)
		return (NULL);
	if (is_minus)
		s[0] = '-';
	while (digit - is_minus)
	{
		s[(digit--) - 1] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (s);
}
