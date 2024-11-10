/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:49:16 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/08 19:59:08 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_sms(struct timeval tv)
{
	unsigned long	ms;

	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

unsigned long	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (get_sms(tv) - philo->sms);
}

unsigned long	get_time_d(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (get_sms(tv) - get_sms(data->start_time));
}

unsigned long	get_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (get_sms(now));
}

void	msleep(unsigned long ms, t_philo *philo)
{
	(void) philo;
	usleep(ms * 1000);
	// unsigned long	start;

	// start = get_now();
	// while (get_now() - start < ms)
	// {
	// 	if (safe_read_end(philo->end_lock, philo->end))
	// 		break ;
	// 	usleep(ms / 10);
	// }
	//idfk what i should do here fuck this shitty project
	//rest is fixed tho
}
