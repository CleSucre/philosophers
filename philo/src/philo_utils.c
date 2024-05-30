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

int	ft_print(t_philo *philo, char *str)
{
	char	*tmp;

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
	return (0);
}

int	is_dead(t_philo *philo)
{
	if (philo->last_meal + philo->settings->ttd < current_time_in_ms()
		&& !philo->shared->stop)
	{
		philo->dead = 1;
		philo->shared->stop = 1;
		ft_print(philo, "died");
		pthread_mutex_unlock(&philo->shared->lock);
		return (1);
	}
	if (philo->shared->stop)
	{
		pthread_mutex_unlock(&philo->shared->lock);
		return (1);
	}
	return (0);
}

static void	lock(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->shared->forks[philo->id].lock);
		pthread_mutex_lock(&philo->shared->forks[
			(philo->id + 1) % philo->settings->np].lock);
	}
	else
	{
		pthread_mutex_lock(&philo->shared->forks[
			(philo->id + 1) % philo->settings->np].lock);
		pthread_mutex_lock(&philo->shared->forks[philo->id].lock);
	}
}

void	give_forks(t_philo *philo)
{
	lock(philo);
	philo->shared->forks[philo->id].used = 0;
	philo->shared->forks[(philo->id + 1) % philo->settings->np].used = 0;
	pthread_mutex_unlock(&philo->shared->forks[philo->id].lock);
	pthread_mutex_unlock(&philo->shared->forks[
		(philo->id + 1) % philo->settings->np].lock);
	philo->meals++;
	philo->last_meal = current_time_in_ms();
	if (philo->meals == philo->settings->me)
		philo->full = 1;
}

int	take_forks(t_philo *philo)
{
	if (philo->settings->np == 1)
	{
		pthread_mutex_unlock(&philo->shared->lock);
		return (0);
	}
	lock(philo);
	if (philo->shared->forks[philo->id].used
		|| philo->shared->forks[(philo->id + 1) % philo->settings->np].used)
	{
		philo->shared->forks[philo->id].used = 1;
		philo->shared->forks[(philo->id + 1) % philo->settings->np].used = 1;
		pthread_mutex_unlock(&philo->shared->forks[philo->id].lock);
		pthread_mutex_unlock(&philo->shared->forks[
			(philo->id + 1) % philo->settings->np].lock);
		pthread_mutex_unlock(&philo->shared->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->forks[philo->id].lock);
	pthread_mutex_unlock(&philo->shared->forks[
		(philo->id + 1) % philo->settings->np].lock);
	return (1);
}
