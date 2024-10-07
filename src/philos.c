/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:27:21 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/07 17:05:40 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_data *data, t_philo *philo, int id)
{
	philo->start_lock = &data->start_lock;
	philo->end_lock = &data->end_lock;
	philo->write_lock = &data->write_lock;
	philo->done_lock = &data->done_lock;
	philo->total_philo_done = &data->total_philo_done;
	pthread_mutex_init(&philo->meal_lock, NULL);
	philo->meal_goal = data->meal_goal;
	philo->id = id;
	philo->left_fork = &data->forks[id];
	philo->right_fork = &data->forks[(id + 1) % data->nb_philos];
	philo->end = &data->end;
	philo->nb_philos = data->nb_philos;
	philo->start_time = &data->start_time;
	philo->time_to_eat = data->tte;
	philo->time_to_sleep = data->tts;
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = ft_calloc(data->nb_philos, sizeof(t_philo));
	while (i < data->nb_philos)
	{
		init_philo(data, &data->philos[i], i);
		i++;
	}
}

void	start_philos(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->start_lock);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philo_start, (void *)(&data->philos[i]));
		i += 2;
	}
	i = 1;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philo_start, (void *)(&data->philos[i]));
		i += 2;
	}
	gettimeofday(&data->start_time, NULL);
	pthread_mutex_unlock(&data->start_lock);
}

void	*join_philos(t_data *data)
{
	(void) data;
	return (NULL);
}

void	*philo_start(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->start_lock);
	philo->sms = get_ms(*philo->start_time);
	pthread_mutex_unlock(philo->start_lock);
	while (!safe_read_end(philo->end_lock, philo->end))
	{
		if (philo->id % 2)
			take_forks(philo, philo->left_fork, philo->right_fork);
		else
			take_forks(philo, philo->right_fork, philo->left_fork);
		if (philo->nb_philos == 1)
			break ;
		pthread_mutex_lock(philo->write_lock);
		eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_and_think(philo);
	}
	return (NULL);
}
