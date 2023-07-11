/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:32:35 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:04:58 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_mutex_array(t_table *table)
{
	pthread_mutex_t	*mutex_per_forks_array;
	unsigned int	i;

	mutex_per_forks_array = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!mutex_per_forks_array)
		return (error_null(ERROR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&mutex_per_forks_array[i], 0) != 0)
			return (error_null(ERROR_MUTEX, NULL, 0));
		i++;
	}
	return (mutex_per_forks_array);
}

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nbr_philos;
	if ((philo->id % 2) != 0)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->nbr_philos;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philos(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!philos)
		return (error_null(ERROR_MALLOC, NULL, 0));
	i = 0;
	while (i < table->nbr_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (error_null(ERROR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&philos[i]->meal_time_mutex, 0) != 0)
			return (error_null(ERROR_MUTEX, NULL, 0));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

static bool	init_general_mutex(t_table *table)
{
	table->fork_mutex = init_mutex_array(table);
	if (!table->fork_mutex)
		return (false);
	if (pthread_mutex_init(&table->simu_status_mutex, 0) != 0)
		return (error_failure(ERROR_MUTEX, NULL, table));
	if (pthread_mutex_init(&table->write_mutex, 0) != 0)
		return (error_failure(ERROR_MUTEX, NULL, table));
	return (true);
}

t_table	*init_table(int argc, char **argv, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_null(ERROR_MALLOC, NULL, 0));
	table->nbr_philos = atoi_positive_int(argv[i++]);
	table->time_to_die = atoi_positive_int(argv[i++]);
	table->time_to_eat = atoi_positive_int(argv[i++]);
	table->time_to_sleep = atoi_positive_int(argv[i++]);
	table->must_eat_count = -1;
	if (argc - 1 == 5)
		table->must_eat_count = atoi_positive_int(argv[i]);
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	if (!init_general_mutex(table))
		return (NULL);
	table->simu_status = false;
	return (table);
}
