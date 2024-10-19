/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:20:58 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/19 04:35:46 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo, pthread_mutex_t *fst, pthread_mutex_t *snd)
{
	pthread_mutex_lock(fst);
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->write_lock);
	if (philo->nb_philos == 1)
		return ;
	pthread_mutex_lock(snd);
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->write_lock);
}

void	eat(t_philo *philo)
{
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
	better_usleep(philo->time_to_eat);
}

void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "is sleeping");
	pthread_mutex_unlock(philo->write_lock);
	better_usleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "is thinking");
	pthread_mutex_unlock(philo->write_lock);
}
