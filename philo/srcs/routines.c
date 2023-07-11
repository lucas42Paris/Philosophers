/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:16:21 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:05:30 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutex[philo->fork[0]]);
	write_status(philo, false, FORK_1);
	pthread_mutex_lock(&philo->table->fork_mutex[philo->fork[1]]);
	write_status(philo, false, FORK_2);
	write_status(philo, false, EAT);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	pause_philo(philo->table, philo->table->time_to_eat);
	if (has_simulation_stopped(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_mutex);
	}
	write_status(philo, false, SLEEP);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork[0]]);
	pause_philo(philo->table, philo->table->time_to_sleep);
}

static void	think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_mutex);
	time_to_think = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal_time)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(philo, false, THINK);
	pause_philo(philo->table, time_to_think);
}

static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutex[philo->fork[0]]);
	write_status(philo, false, FORK_1);
	pause_philo(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork[0]]);
	return (NULL);
}

void	*philosophers(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	delay(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nbr_philos == 1)
		return (single_philo(philo));
	else if ((philo->id % 2) != 0)
		think(philo, true);
	while (has_simulation_stopped(philo->table) == false)
	{
		eat_sleep(philo);
		think(philo, false);
	}
	return (NULL);
}
