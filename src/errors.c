/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:54:12 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/06 20:30:18 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *err)
{
	ft_putstr_fd(err, 2);
	exit(EXIT_FAILURE);
}

bool	is_numeric(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

void	check_for_invalid_argument(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_numeric(av[i]))
			error("error: invalid argument\n");
		i++;
	}
}

void	usage_error(char **av)
{
	ft_putstr_fd("error: usage: ", 2);
	ft_putstr_fd(av[0], 2);
	ft_putstr_fd(" philo_count time_to_die time_to_eat", 2);
	ft_putstr_fd(" time_to_sleep [meal_count_goal]\n", 2);
	exit(EXIT_FAILURE);
}
