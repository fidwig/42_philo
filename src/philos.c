/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:27:21 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/05 18:18:35 by jsommet          ###   ########.fr       */
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
	philo->state = 0;
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
	data->philos = calloc(data->nb_philos, sizeof(t_philo));
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
	// usleep((suseconds_t) 1);
	pthread_mutex_unlock(philo->start_lock);
	while (!safe_read_end(philo->end_lock, philo->end))
	{
		if (philo->id % 2)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->write_lock);
			if (!safe_read_end(philo->end_lock, philo->end))
				write_log(get_time(philo), philo->id, "has taken a fork");
			pthread_mutex_unlock(philo->write_lock);
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->write_lock);
			if (!safe_read_end(philo->end_lock, philo->end))
				write_log(get_time(philo), philo->id, "has taken a fork");
			pthread_mutex_unlock(philo->write_lock);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->write_lock);
			if (!safe_read_end(philo->end_lock, philo->end))
				write_log(get_time(philo), philo->id, "has taken a fork");
			pthread_mutex_unlock(philo->write_lock);
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->write_lock);
			if (!safe_read_end(philo->end_lock, philo->end))
				write_log(get_time(philo), philo->id, "has taken a fork");
			pthread_mutex_unlock(philo->write_lock);
		}
		pthread_mutex_lock(philo->write_lock);
		if (!safe_read_end(philo->end_lock, philo->end))
			write_log(get_time(philo), philo->id, "is eating");
		pthread_mutex_unlock(philo->write_lock);
		philo->meal_count++;
		if (philo->meal_count == philo->meal_goal)
		{
			pthread_mutex_lock(philo->done_lock);
			(*philo->total_philo_done)++;
			if (*philo->total_philo_done == philo->nb_philos)
				safe_write_end(philo->end_lock, philo->end, true);
			pthread_mutex_unlock(philo->done_lock);
		}
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal = get_time(philo);
		pthread_mutex_unlock(&philo->meal_lock);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		pthread_mutex_lock(philo->write_lock);
		if (!safe_read_end(philo->end_lock, philo->end))
			write_log(get_time(philo), philo->id, "is sleeping");
		pthread_mutex_unlock(philo->write_lock);
		usleep(philo->time_to_sleep * 1000);

		pthread_mutex_lock(philo->write_lock);
		if (!safe_read_end(philo->end_lock, philo->end))
			write_log(get_time(philo), philo->id, "is thinking");
		pthread_mutex_unlock(philo->write_lock);
	}
	return (NULL);
}
