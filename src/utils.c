/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:58:52 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/03 19:49:07 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	i;

	i = nmemb * size;
	if (i != 0 && i / nmemb != size)
		return (NULL);
	s = malloc(i);
	if (!s)
		return (NULL);
	memset(s, 0, i);
	return (s);
}

static int	ft_ise(int c)
{
	return ((c >= 9 && c <= 13) || c == 0 || c == 32);
}

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		s;
	long	n;

	i = 0;
	s = 1;
	n = 0;
	while (ft_ise(nptr[i]) && nptr[i])
		i++;
	if ((nptr[i] == '+' || nptr[i] == '-') && nptr[i])
	{
		if (nptr[i] == '-')
			s = -s;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i])
		n = n * 10 + (nptr[i++] - '0');
	return ((int)n * s);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}
