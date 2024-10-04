/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:16:05 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/04 17:07:46 by jsommet          ###   ########.fr       */
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
	init_philos(data);
	data->ttd = (t_ms) ft_atoi(av[2]);
	data->tte = (t_ms) ft_atoi(av[3]);
	data->tts = (t_ms) ft_atoi(av[4]);
	data->meal_goal = -1;
	if (data->ac > 5)
		data->meal_goal = ft_atoi(av[5]);
	// printf("ttd%zu tte%zu tts%zu mg%d", data->ttd, data->tte, data->tts, data->meal_goal);
}

void	clear_data(t_data *data)
{
	(void) data;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		return (1);
	init_data(&data, ac, av);
	init_philos(&data);
	run(&data);
	return (0);
}
