/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:34:36 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:05:13 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_simu(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_in_ms() + (table->nbr_philos * 2 * 10);
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, &philosophers,
				table->philos[i]) != 0)
			return (error_failure(ERROR_THREAD, NULL, table));
		i++;
	}
	if (table->nbr_philos > 1)
	{
		if (pthread_create(&table->supervisor, NULL, &supervisor, table) != 0)
			return (error_failure(ERROR_THREAD, NULL, table));
	}
	return (true);
}

static void	stop_simu(t_table	*table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nbr_philos > 1)
		pthread_join(table->supervisor, NULL);
	destroy_all_mutex(table);
	free_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc - 1 < 4 || argc - 1 > 5)
		return (msg(ERROR_ARGCS, NULL, EXIT_FAILURE));
	if (!is_valid_argcs(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simu(table))
		return (EXIT_FAILURE);
	stop_simu(table);
	return (EXIT_SUCCESS);
}
