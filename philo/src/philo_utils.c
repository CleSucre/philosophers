/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:00:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/26 05:00:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

int	ft_print(t_philo *philo, char *str)
{
	char	*tmp;

	pthread_mutex_lock(&philo->shared->lock);
	tmp = ft_itoa(current_time_in_ms() - philo->shared->start_ms);
	ft_fputstr(1, tmp);
	free(tmp);
	ft_fputstr(1, " ");
	tmp = ft_itoa(philo->id);
	ft_fputstr(1, tmp);
	free(tmp);
	ft_fputstr(1, " ");
	ft_fputstr(1, str);
	ft_fputstr(1, "\n");
	pthread_mutex_unlock(&philo->shared->lock);
	return (0);
}
