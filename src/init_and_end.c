/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:00:12 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/03 20:35:27 by jsommet          ###   ########.fr       */
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
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		clean_exit(data, EXIT_FAILURE);
	philo->meal_goal = data->meal_goal;
	philo->id = id + 1;
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
	if (!data->philos)
		clean_exit(data, EXIT_FAILURE);
	while (i < data->nb_philos)
	{
		init_philo(data, &data->philos[i], i);
		i++;
	}
}

void	data_mutex_init_and_allocs(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
		clean_exit(data, EXIT_FAILURE);
	if (pthread_mutex_init(&data->end_lock, NULL) != 0)
		clean_exit(data, EXIT_FAILURE);
	if (pthread_mutex_init(&data->done_lock, NULL) != 0)
		clean_exit(data, EXIT_FAILURE);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		clean_exit(data, EXIT_FAILURE);
	i = 0;
	data->forks = ft_calloc(data->nb_philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		clean_exit(data, EXIT_FAILURE);
	while (i < data->nb_philos)
		if (pthread_mutex_init(&data->forks[i++], NULL))
			clean_exit(data, EXIT_FAILURE);
}

void	init_data(t_data *data, int ac, char **av)
{
	check_for_invalid_argument(ac, av);
	*data = (t_data){0};
	data->ac = ac;
	data->av = av;
	data->nb_philos = ft_atoi(av[1]);
	data_mutex_init_and_allocs(data);
	data->ttd = (t_sms) ft_atoi(av[2]);
	data->tte = (t_sms) ft_atoi(av[3]);
	data->tts = (t_sms) ft_atoi(av[4]);
	data->meal_goal = -1;
	if (data->ac > 5)
		data->meal_goal = ft_atoi(av[5]);
	init_philos(data);
}

void	clear_data(t_data *data)
{
	int	i;

	i = -1;
	while (data->forks && ++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	i = -1;
	while (data->philos && ++i < data->nb_philos)
		pthread_mutex_destroy(&data->philos[i].meal_lock);
	free(data->philos);
	pthread_mutex_destroy(&data->done_lock);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->start_lock);
}
