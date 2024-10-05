/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:15:48 by jsommet           #+#    #+#             */
/*   Updated: 2024/10/05 17:49:53 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

typedef unsigned long	t_ms;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				state;

	int				meal_count;
	int				meal_goal;
	int				*total_philo_done;
	struct timeval	*start_time;
	t_ms			time_to_eat;
	t_ms			time_to_sleep;
	suseconds_t		sms;
	t_ms			last_meal;

	int				nb_philos;

	bool			*end;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*end_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*done_lock;
	pthread_mutex_t	*start_lock;
}	t_philo;

typedef struct s_data
{
	int				ac;
	char			**av;

	t_ms			ttd;
	t_ms			tte;
	t_ms			tts;
	int				meal_goal;
	int				nb_philos;
	int				total_philo_done;
	t_philo			*philos;
	struct timeval	start_time;

	bool			end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	done_lock;
	pthread_mutex_t	start_lock;
}	t_data;

bool			safe_read_end(pthread_mutex_t *end_lock, bool *end);
bool			safe_write_end(pthread_mutex_t *end_lock,
					bool *dead, bool val);
int				safe_write_log(pthread_mutex_t *wlck,
					suseconds_t ts, int id, char *act);
int				write_log(suseconds_t ts, int id, char *act);
void			safe_putstr(pthread_mutex_t *write_lock, char *str);
void			init_philo(t_data *data, t_philo *philo, int id);
void			init_philos(t_data *data);
void			start_philos(t_data *data);
void			*join_philos(t_data *data);
void			*philo_start(void *arg);
void			run(t_data *data);

unsigned long	get_ms(struct timeval tv);
unsigned long	get_time(t_philo *philo);
unsigned long	get_time_d(t_data *data);

void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *nptr);
#endif // !PHILOSOPHERS_H