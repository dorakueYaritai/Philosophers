/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:57:31 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/19 18:12:19 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_toupper(int c);
int	ft_isalnum(int c);
int	ft_isdigit(int c);
int	ft_isalpha(int c);

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 'b' - 'B';
	return (c);
}

