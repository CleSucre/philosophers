/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:00:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/26 05:00:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	ft_nbrlen(long n)
{
	size_t	i;

	i = 1;
	if (0 > n)
	{
		n *= -1;
		i++;
	}
	while (9 < n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_insert(char *dst, long n, int *i)
{
	if (n > 9)
	{
		ft_insert(dst, n / 10, i);
		ft_insert(dst, n % 10, i);
	}
	else
		dst[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*res;
	long	num;
	int		i;

	num = n;
	res = (char *)malloc(sizeof(char) * (ft_nbrlen(num) + 1));
	if (!res)
		return (NULL);
	i = 0;
	if (num < 0)
	{
		res[i++] = '-';
		num *= -1;
	}
	ft_insert(res, num, &i);
	res[i] = '\0';
	return (res);
}
