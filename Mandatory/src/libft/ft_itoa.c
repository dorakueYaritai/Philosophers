/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:09:20 by hioikawa          #+#    #+#             */
/*   Updated: 2023/03/30 20:54:03 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	count_dig(int n)
{
	size_t	dig;

	dig = 0;
	if (n <= 0)
		dig = 1;
	while (n != 0)
	{
		n /= 10;
		dig++;
	}
	return (dig);
}

static char	*to_char(int n, int sign, size_t dig)
{
	char	*toa;
	size_t	i;
	size_t	j;

	toa = (char *)ft_calloc(1, sizeof(char) * (dig + 1));
	if (toa == NULL)
		return (NULL);
	i = 0;
	j = dig - 1;
	while (i < dig)
	{
		if (n == 0 && sign < 0)
			toa[0] = '-';
		else
			toa[j] = n % 10 * sign + '0';
		n /= 10;
		i++;
		j--;
	}
	return (toa);
}

char	*ft_itoa(int n)
{
	char	*toa;
	size_t	dig;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	dig = count_dig(n);
	toa = to_char(n, sign, dig);
	return (toa);
}
/*
int main()
{
	printf("\t%11s\n", ft_itoa(0));
	printf("\t%11s\n", ft_itoa(-0));
	printf("\t%11s\n", ft_itoa(12345));
	printf("\t%11s\n", ft_itoa(INT_MAX));
	printf("\t%11s\n", ft_itoa(INT_MIN));
	printf("\t%11s\n", ft_itoa(UINT_MAX));
	size_t n;
	n = INT_MAX;
	n += 10;
	printf("\t%11s\n", ft_itoa(n));
	n = INT_MIN;
	n -= 10;
	printf("\t%11s\n", ft_itoa(n));
}
*/
