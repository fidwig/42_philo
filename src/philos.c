/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:27:21 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/07 16:59:25 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_philos(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->start_lock);
	gettimeofday(&data->start_time, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philo_start, (void *)(&data->philos[i]));
		i += 2;
	}
	pthread_mutex_unlock(&data->start_lock);
	usleep(240);
	pthread_mutex_lock(&data->start_lock);
	i = 1;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philo_start, (void *)(&data->philos[i]));
		i += 2;
	}
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
	philo->sms = get_sms(*philo->start_time);
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
