/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:00:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/26 05:00:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
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

static void	give_forks(t_philo *philo)
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

static int	take_forks(t_philo *philo)
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

void	*run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->shared->lock);
		if (is_dead(philo))
			break ;
		if (!take_forks(philo))
			continue ;
		ft_print(philo, "has taken a fork");
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		pthread_mutex_unlock(&philo->shared->lock);
		usleep(philo->settings->tte * 1000);
		pthread_mutex_lock(&philo->shared->lock);
		if (is_dead(philo))
			break ;
		give_forks(philo);
		ft_print(philo, "is sleeping");
		pthread_mutex_unlock(&philo->shared->lock);
		usleep(philo->settings->tts * 1000);
		pthread_mutex_lock(&philo->shared->lock);
		if (is_dead(philo))
			break ;
		ft_print(philo, "is thinking");
		pthread_mutex_unlock(&philo->shared->lock);
		if (philo->full)
			break ;
	}
	return (NULL);
}
