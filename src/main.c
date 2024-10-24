/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:16:05 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/07 16:52:36 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, int ac, char **av)
{
	int	i;

	*data = (t_data){0};
	data->ac = ac;
	data->av = av;
	data->nb_philos = ft_atoi(av[1]);
	pthread_mutex_init(&data->start_lock, NULL);
	pthread_mutex_init(&data->end_lock, NULL);
	pthread_mutex_init(&data->done_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	i = 0;
	data->forks = ft_calloc(data->nb_philos, sizeof(pthread_mutex_t));
	while (i < data->nb_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->ttd = (t_sms) ft_atoi(av[2]);
	data->tte = (t_sms) ft_atoi(av[3]);
	data->tts = (t_sms) ft_atoi(av[4]);
	data->meal_goal = -1;
	if (data->ac > 5)
		data->meal_goal = ft_atoi(av[5]);
	init_philos(data);
	if (data->nb_philos < 0
		|| data->ttd < 0 || data->tte < 0 || data->tts < 0)
		error(data);
}

void	clear_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->philos[i].meal_lock);
	free(data->philos);
	pthread_mutex_destroy(&data->done_lock);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->start_lock);
}

void	error(t_data *data)
{
	printf("error\n");
	clear_data(data);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		return (1);
	init_data(&data, ac, av);
	run(&data);
	clear_data(&data);
	return (0);
}
