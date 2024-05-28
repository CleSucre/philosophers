/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:00:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/26 05:00:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_value(const char *str)
{
	long int	num;
	int			is_n;

	while (ft_isspace(*str))
		str++;
	is_n = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			is_n = 1;
	while (*str == '0')
		str++;
	num = 0;
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0');
	if (*str != '\0')
		return (0);
	str--;
	if (num == 0 && *str != '0')
		return (0);
	if (is_n)
		num *= -1;
	if (num > 2147483647 || num < 0)
		return (0);
	return (1);
}

int	parsing(char **argv, t_settings *settings)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_value(argv[i]))
			return (0);
		i++;
	}
	settings->np = ft_atoi(argv[1]);
	if (settings->np < MIN_PHILOSOPHERS || settings->np > MAX_PHILOSOPHERS)
		return (0);
	settings->ttd = ft_atoi(argv[2]);
	settings->tte = ft_atoi(argv[3]);
	settings->tts = ft_atoi(argv[4]);
	if (argv[5])
		settings->me = ft_atoi(argv[5]);
	else
		settings->me = 0;
	return (1);
}
