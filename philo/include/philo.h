/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:00:00 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/26 05:00:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define MIN_PHILOSOPHERS 1
# define MAX_PHILOSOPHERS 2000

typedef struct s_settings
{
	int				np;
	int				ttd;
	int				tte;
	int				tts;
	int				me;
}						t_settings;

typedef struct s_fork
{
	int				owner;
	int				used;
	void			*next;
	void			*prev;
	pthread_mutex_t	lock;
}						t_fork;

typedef struct s_shared
{
	long long		start_ms;
	int				stop;
	t_fork			*forks;
	pthread_mutex_t	lock;
}						t_shared;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals;
	int				dead;
	int				full;
	t_shared		*shared;
	t_settings		*settings;
}						t_philo;

// ################## CONVERTER ##################

int			ft_atoi(char *str);
char		*ft_itoa(int n);

// #################### MANAGER ##################

void		init_shared_data(t_shared *shared, t_settings *settings);
int			init_memory(pthread_t **threads, t_shared *shared,
				t_philo **philo, t_settings *settings);
void		init_philo(t_philo *philo, t_shared *shared,
				t_settings *settings, int id);

// #################### PARSING ##################

int			parsing(char **argv, t_settings *settings);

// #################### THREAD ###################

void		*run(void *arg);

// ################# PHILO_UTILS #################

long long	current_time_in_ms(void);
int			ft_print(t_philo *philo, char *str);

// ##################### UTILS ###################

int			ft_isdigit(int c);
int			ft_isspace(int c);
int			ft_strlen(char *str);
int			ft_fputstr(int fd, char *str);

#endif
