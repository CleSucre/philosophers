/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:00:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/26 05:00:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(pthread_t *threads, t_philo *philo, int np)
{
	int	i;

	i = 0;
	while (i < np)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&philo->shared->forks[i].lock);
		i++;
	}
	pthread_mutex_destroy(&philo->shared->lock);
	free(threads);
	free(philo->shared->forks);
	free(philo);
}

static void	wait_threads(pthread_t *threads, t_philo *philo, int np)
{
	int	i;
	int	fulls;

	i = -1;
	fulls = 0;
	while (++i < np)
	{
		if (philo[i].dead || fulls == np)
		{
			philo->shared->stop = 1;
			break ;
		}
		if (philo[i].full)
			fulls++;
		else
			fulls = 0;
		if (i == np)
			i = -1;
	}
	free_all(threads, philo, np);
}

static int	start_pool(t_settings settings)
{
	pthread_t	*threads;
	t_shared	shared;
	t_philo		*philo;
	int			i;

	if (!init_memory(&threads, &shared, &philo, &settings))
		return (0);
	i = 0;
	while (i < settings.np)
	{
		init_philo(philo, &shared, &settings, i);
		if (pthread_create(&threads[i], NULL, run, &philo[i]))
		{
			free(philo);
			free(threads);
			return (0);
		}
		i++;
	}
	wait_threads(threads, philo, settings.np);
	return (1);
}

int	main(int argc, char **argv)
{
	t_settings	settings;

	if (argc < 5)
	{
		ft_fputstr(2, "Usage: ./philo number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (!parsing(argv, &settings))
	{
		ft_fputstr(2, "Error: invalid argument\n");
		return (1);
	}
	start_pool(settings);
	return (0);
}
