/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:42:27 by kakiba            #+#    #+#             */
/*   Updated: 2023/03/18 20:12:35 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <limits.h>

typedef struct s_data t_data;
struct s_data{
	int		num1;
	int		num2;
	char	ch1;
	char	ch2;
	char	ch3;
	char	ch4;
};

// int	main()
// {
// 	t_data	data;

// 	printf("%p\n", data);

// 	printf("size: %ld\n", sizeof(t_data));
// 	printf("size: %ld\n", sizeof(t_data *));

// 	printf("%p\n", data.ch1);
// 	printf("%p\n", data.ch2);
// 	printf("%p\n", data.ch3);
// 	printf("%p\n", data.ch4);
// 	printf("%p\n", data.num1);
// 	printf("%p\n", data.num2);
// 	printf("%x\n", data.ch1);
// 	printf("%c\n", data.ch2);
// 	printf("%c\n", data.ch3);
// 	printf("%c\n", data.ch4);
// 	printf("%d\n", data.num1);
// 	printf("%d\n", data.num2);
// }

void	print_data(t_data data)
{
	printf("%d\n", data.num1);
	printf("%c\n", data.ch1);
	printf("%c\n", data.ch2);
	printf("%c\n", data.ch3);
	printf("%c\n", data.ch4);
	printf("%d\n", data.num2);
	printf("-----\n");
}

void	print_data_p(t_data *data)
{
	printf("%d\n", data->num1);
	printf("%c\n", data->ch1);
	printf("%c\n", data->ch2);
	printf("%c\n", data->ch3);
	printf("%c\n", data->ch4);
	printf("%d\n", data->num2);
	printf("-----\n");
}

int	main()
{
	t_data	data;
	t_data	data2;
	t_data	*data3;
	char	*ptr;

	printf("dead check pointer:%p\n", data);
	memset(&data, 0, sizeof(data));
	printf("size: %ld\n", sizeof(t_data));
	printf("%p\n", &data.num1);

	data.ch1 = 'A';
	data.ch2 = 'B';
	data.ch3 = 'C';
	data.ch4 = 'D';
	data.num1 = 0xffffffff;
	data.num2 = 0b01111111111111111111111111111111;
	// data.num1 += INT_MAX;
	// data.num1 = 0b10000000000000000000000000000000;
	// data.num2 = 0xfffffff;

	print_data(data);
	print_data(data2);

	data2 = data;
	print_data(data2);

	// printf("%d\n", data);
	printf("%d\n", data.num1);
	printf("%d\n", data.num2);
	printf("-----a\n");
	printf("%ld\n", data);
	printf("%ld\n", data2);
	printf("-----a\n");

	printf("%p\n", &data.num2);
	printf("-----\n");
	printf("%p\n", &data2.num2);
	printf("-----\n");

	data2.num1 = 100;
	data2.num2 = 200;
	print_data(data2);

	// data3 = &data2;
	// print_data_p(data3);

	// data3->num1 = 65;
	// data3->ch1 = 'E';
	// data3->ch2 = 'F';
	// data3->ch3 = 'G';
	// data3->ch4 = 'H';
	// data3->num2 = 80;

	// print_data_p(data3);
	// print_data(data2);
	// print_data(data);
}