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
	pthread_mutex_lock(&philo->shared->lock);
	lock(philo);
	philo->shared->forks[philo->id].used = 0;
	philo->shared->forks[(philo->id + 1) % philo->settings->np].used = 0;
	pthread_mutex_unlock(&philo->shared->forks[philo->id].lock);
	pthread_mutex_unlock(&philo->shared->forks[
		(philo->id + 1) % philo->settings->np].lock);
	pthread_mutex_unlock(&philo->shared->lock);
	philo->meals++;
	philo->last_meal = current_time_in_ms();
	if (philo->meals == philo->settings->me)
		philo->full = 1;
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->lock);
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
	pthread_mutex_unlock(&philo->shared->lock);
	return (1);
}

void	*run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->last_meal + philo->settings->ttd < current_time_in_ms())
		{
			philo->dead = 1;
			ft_print(philo, "died");
			break ;
		}
		if (!take_forks(philo))
			continue ;
		ft_print(philo, "has taken a fork");
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		usleep(philo->settings->tte);
		give_forks(philo);
		ft_print(philo, "is sleeping");
		usleep(philo->settings->tts);
		ft_print(philo, "is thinking");
		if (philo->full)
			break ;
	}
	return (NULL);
}
