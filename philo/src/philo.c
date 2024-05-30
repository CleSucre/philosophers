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

static void	*philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->lock);
	if (is_dead(philo))
		return (NULL);
	if (!take_forks(philo))
	{
		pthread_mutex_unlock(&philo->shared->lock);
		return ((void *)1);
	}
	ft_print(philo, "has taken a fork");
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_unlock(&philo->shared->lock);
	usleep(philo->settings->tte * 1000);
	return ((void *)1);
}

static void	*philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->lock);
	if (is_dead(philo))
		return (NULL);
	give_forks(philo);
	ft_print(philo, "is sleeping");
	pthread_mutex_unlock(&philo->shared->lock);
	usleep(philo->settings->tts * 1000);
	return ((void *)1);
}

static void	*philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->lock);
	if (is_dead(philo))
		return (NULL);
	ft_print(philo, "is thinking");
	pthread_mutex_unlock(&philo->shared->lock);
	return ((void *)1);
}

static void	*philo_activity_cycle(t_philo *philo)
{
	if (philo_eat(philo) == NULL)
		return (NULL);
	if (philo_sleep(philo) == NULL)
		return (NULL);
	if (philo_think(philo) == NULL)
		return (NULL);
	return ((void *)1);
}

void	*run(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_activity_cycle(philo) == NULL)
			break ;
		if (philo->full)
			break ;
	}
	return (NULL);
}
