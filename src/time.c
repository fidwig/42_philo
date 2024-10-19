/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:49:16 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/19 06:04:18 by jsommet          ###   ########.fr       */
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

unsigned long	get_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (get_ms(now));
}

// void	better_usleep(unsigned long ms)
// {
// 	usleep(ms * 1000);
// }

// void	better_usleep(unsigned long ms)
// {
// 	unsigned long	start;
// 	suseconds_t		better;

// 	better = ms / BETTER_SLEEP_TIME;
// 	start = get_now();
// 	while (get_now() - start < ms - better)
// 		usleep(better * 1000);
// }

void	better_usleep(unsigned long ms)
{
	unsigned long	count;
	unsigned long	last;

	count = ms / BETTER_SLEEP_TIME;
	last = ms % BETTER_SLEEP_TIME;
	while (--count > 0)
		usleep(BETTER_SLEEP_TIME * 1000);
	if (last > 0)
		usleep(last * 1000);
}
