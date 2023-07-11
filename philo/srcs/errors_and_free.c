/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:54:31 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:04:40 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_mutex != NULL)
		free(table->fork_mutex);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

void	destroy_all_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->simu_status_mutex);
}


int	msg(char *str, char *error_error_details, int exit_nbr)
{
	if (!error_error_details)
		printf(str, PROG_NAME);
	else
		printf(str, PROG_NAME, error_error_details);
	return (exit_nbr);
}

int	error_failure(char *str, char *error_details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (msg(str, error_details, 0));
}

void	*error_null(char *str, char *error_details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, error_details, EXIT_FAILURE);
	return (NULL);
}
