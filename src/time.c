/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:49:16 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/04 16:42:36 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_ms(struct timeval tv)
{
	unsigned long	ms;

	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

unsigned long	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (get_ms(tv) - philo->sms);
}

unsigned long	get_time_d(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (get_ms(tv) - get_ms(data->start_time));
}
