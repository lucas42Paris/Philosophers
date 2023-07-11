/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:41:08 by lsalin            #+#    #+#             */
/*   Updated: 2022/11/16 12:50:59 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_simu_status(t_table *table, bool simu_status)
{
	pthread_mutex_lock(&table->simu_status_mutex);
		table->simu_status = simu_status;
	pthread_mutex_unlock(&table->simu_status_mutex);
}

bool	has_simulation_stopped(t_table *table)
{
	bool	b;

	b = false;
	pthread_mutex_lock(&table->simu_status_mutex);
	if (table->simu_status == true)
		b = true;
	pthread_mutex_unlock(&table->simu_status_mutex);
	return (b);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal_time) >= philo->table->time_to_die)
	{
		set_simu_status(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_mutex);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_mutex);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate < (unsigned int)
				table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_mutex);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		set_simu_status(table, true);
		return (true);
	}
	return (false);
}

void	*supervisor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	set_simu_status(table, false);
	delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
