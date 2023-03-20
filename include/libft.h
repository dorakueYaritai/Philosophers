/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:58:16 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/20 09:58:42 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBFFT_H
#define LIBFFT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

// libft
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_itoa(int n);
char		*ft_ltoa(long n);
int			 ft_positive_mod(int dividend, int divisor);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit_str(char *str, size_t sign_allowable);
long		ft_strtol(const char *nptr, char **endptr, int base);
int			ft_toupper(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);

#endif