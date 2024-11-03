/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:16:05 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/03 20:31:49 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		usage_error(av);
	init_data(&data, ac, av);
	run(&data);
	clear_data(&data);
	return (EXIT_SUCCESS);
}

void	clean_exit(t_data *data, int exit_code)
{
	if (data)
		clear_data(data);
	exit(exit_code);
}
