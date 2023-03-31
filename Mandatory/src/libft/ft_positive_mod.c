/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_positive_mod.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:10:45 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/30 20:54:29 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_positive_mod(int dividend, int divisor)
{
	int	ans;

	ans = dividend % divisor;
	if (ans < 0)
		ans += divisor;
	return (ans);
}
