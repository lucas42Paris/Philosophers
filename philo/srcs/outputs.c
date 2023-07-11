/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:39:14 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:05:19 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, bool supervisor_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (has_simulation_stopped(philo->table) == true
		&& supervisor_report == false)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EAT)
		print_status(philo, "is eating");
	else if (status == SLEEP)
		print_status(philo, "is sleeping");
	else if (status == THINK)
		print_status(philo, "is thinking");
	else if (status == FORK_1 || status == FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_mutex);
}
