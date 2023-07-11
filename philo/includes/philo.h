/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:15:23 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:04:12 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"
# define PROG_NAME "philo:"
# define ERROR_ARGCS "\033[0;31mFormat error: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\033[0m\n"
# define ERROR_NBR_PHILOS "\033[0;31mError: there must be between 1 and 250 \
														philosophers\033[0m\n"
# define ERROR_THREAD "\033[0;31mError: thread creation failed\033[0m\n"
# define ERROR_MUTEX "\033[0;31mError: mutex creation failed\033[0m\n"
# define ERROR_DIGITS "\033[0;31mError: digits must be unsigned integers between \
														0 and 2147483647\033[0m\n"
# define ERROR_MALLOC "\033[0;31mError: memory allocation failed\033[0m\n"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	unsigned int	nbr_philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			simu_status;
	pthread_t		supervisor;
	pthread_mutex_t	simu_status_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	unsigned int		fork[2];
	unsigned int		id;
	unsigned int		times_ate;
	time_t				last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		meal_time_mutex;
	t_table				*table;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	FORK_1 = 4,
	FORK_2 = 5
}	t_status;

// main functions
bool		has_simulation_stopped(t_table *table);

// argcs functions
bool		is_valid_argcs(int argc, char **argv);
int			atoi_positive_int(char *str);

// init functions
t_table		*init_table(int argc, char **argv, int i);

// routine functions
void		*philosophers(void *data);
void		pause_philo(t_table *table, time_t sleep_time);

// supervisor thread function
void		*supervisor(void *data);

// time functions
time_t		get_time_in_ms(void);
void		delay(time_t start_time);

// output functions
void		write_status(t_philo *philo, bool reaper, t_status status);

// errors and free functions
void		*free_table(t_table *table);
void		destroy_all_mutex(t_table *table);
int			msg(char *str, char *detail, int exit_nbr);
int			error_failure(char *str, char *error_details, t_table *table);
void		*error_null(char *str, char *error_details, t_table *table);

#endif