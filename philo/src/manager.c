/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:52:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/28 10:52:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_shared_data(t_shared *shared, t_settings *settings)
{
	int		i;
	t_fork	*first_fork;
	t_fork	*tmp_fork;

	shared->start_ms = current_time_in_ms();
	shared->stop = 0;
	i = 0;
	first_fork = &shared->forks[i];
	while (i < settings->np)
	{
		shared->forks[i].used = 0;
		if (i > 0)
		{
			tmp_fork = &shared->forks[i - 1];
			tmp_fork->next = &shared->forks[i];
			shared->forks[i].prev = tmp_fork;
		}
		pthread_mutex_init(&shared->forks[i].lock, NULL);
		i++;
	}
	shared->forks[i - 1].next = first_fork;
	pthread_mutex_init(&shared->lock, NULL);
}

int	init_memory(pthread_t **threads, t_shared *shared,
	t_philo **philo, t_settings *settings)
{
	*threads = malloc(sizeof(pthread_t) * settings->np);
	if (!*threads)
		return (0);
	*philo = malloc(sizeof(t_philo) * settings->np);
	if (!*philo)
	{
		free(*threads);
		return (0);
	}
	shared->forks = malloc(sizeof(t_fork) * settings->np);
	if (!shared->forks)
	{
		free(*threads);
		free(*philo);
		return (0);
	}
	init_shared_data(shared, settings);
	return (1);
}

void	init_philo(t_philo *philo, t_shared *shared,
					t_settings *settings, int id)
{
	philo[id].id = id;
	philo[id].shared = shared;
	philo[id].settings = settings;
	philo[id].last_meal = current_time_in_ms();
	philo[id].meals = 0;
	philo[id].dead = 0;
	philo[id].full = 0;
	philo[id].shared->forks[id].owner = id;
}
