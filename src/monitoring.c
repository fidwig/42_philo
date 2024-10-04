/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:04:11 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/04 16:48:19 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_if_done(t_data *data)
{
	bool	result;

	pthread_mutex_lock(&data->done_lock);
	result = data->total_philo_done == data->nb_philos;
	pthread_mutex_unlock(&data->done_lock);
	return (result);
}

bool	check_for_death(t_data *data, int *id)
{
	int				i;
	unsigned long	t;

	i = 0;
	while (i < data->nb_philos)
	{
		t = get_time_d(data);
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (get_time_d(data) - data->philos[i].last_meal >= data->ttd)
		{
			*id = i;
			pthread_mutex_lock(&data->write_lock);
			write_log(get_time_d(data), i, "died.");
			safe_write_end(&data->end_lock, &data->end, true);
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			return (true);
		}
		pthread_mutex_unlock(&data->philos[i].meal_lock);
	}
	return (false);
}

void	run(t_data *data)
{
	int	id;
	int	i;

	start_philos(data);
	while (true)
	{
		if (check_if_done(data))
		{
			pthread_mutex_lock(&data->write_lock);
			safe_write_end(&data->end_lock, &data->end, true);
			break ;
		}
		else if (check_for_death(data, &id))
		{
			// pthread_mutex_lock(&data->write_lock);
			// safe_set_end(&data->end_lock, &data->end, true);
			// printf("%d %d died.", get_time_d(data), id);
			break ;
		}
	}
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_mutex_unlock(&data->write_lock);
}
