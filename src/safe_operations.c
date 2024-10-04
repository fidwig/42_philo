/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/04 16:41:29 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	safe_read_end(pthread_mutex_t *end_lock, bool *end)
{
	bool	val;

	pthread_mutex_lock(end_lock);
	val = *end;
	pthread_mutex_unlock(end_lock);
	return (val);
}

bool	safe_write_end(pthread_mutex_t *end_lock, bool *end, bool val)
{
	pthread_mutex_lock(end_lock);
	*end = val;
	pthread_mutex_unlock(end_lock);
	return (val);
}

int	safe_write_log(pthread_mutex_t *lock, suseconds_t ts, int id, char *act)
{
	int	return_value;

	pthread_mutex_lock(lock);
	return_value = printf("%zu %d %s\n", ts, id, act);
	pthread_mutex_unlock(lock);
	return (return_value);
}

int	write_log(suseconds_t ts, int id, char *act)
{
	return (printf("%zu %d %s\n", ts, id, act));
}

void	safe_putstr(pthread_mutex_t *write_lock, char *s)
{
	if (!s)
		return ;
	pthread_mutex_lock(write_lock);
	while (*s)
		write(1, s++, 1);
	pthread_mutex_unlock(write_lock);
}
