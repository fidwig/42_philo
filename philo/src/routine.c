/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:20:58 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/08 19:29:46 by jsommet          ###   ########.fr       */
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
	{
		pthread_mutex_unlock(fst);
		return ;
	}
	pthread_mutex_lock(snd);
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->write_lock);
}

void	eat(t_philo *philo)
{
	bool	is_last;

	is_last = false;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time(philo);
	pthread_mutex_unlock(&philo->meal_lock);
	philo->meal_count++;
	if (philo->meal_count == philo->meal_goal)
	{
		pthread_mutex_lock(philo->done_lock);
		(*philo->total_philo_done)++;
		is_last = *philo->total_philo_done == philo->nb_philos;
		if (is_last)
			safe_write_end(philo->end_lock, philo->end, true);
		pthread_mutex_unlock(philo->done_lock);
	}
	if (!safe_read_end(philo->end_lock, philo->end) || is_last)
		write_log(get_time(philo), philo->id, "is eating");
	pthread_mutex_unlock(philo->write_lock);
	msleep(philo->time_to_eat, philo);
}

void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "is sleeping");
	pthread_mutex_unlock(philo->write_lock);
	msleep(philo->time_to_sleep, philo);
	pthread_mutex_lock(philo->write_lock);
	if (!safe_read_end(philo->end_lock, philo->end))
		write_log(get_time(philo), philo->id, "is thinking");
	pthread_mutex_unlock(philo->write_lock);
	if (philo->nb_philos % 2 && philo->time_to_eat + 3 > philo->time_to_sleep)
		msleep(philo->time_to_eat - philo->time_to_sleep + BST, philo);
}
