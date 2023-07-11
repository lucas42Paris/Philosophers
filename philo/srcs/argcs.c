/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:50:34 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 12:04:28 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	contain_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	atoi_positive_int(char *str)
{
	unsigned long long int	nbr;
	int						i;

	i = 0;
	nbr = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return ((int)nbr);
}

bool	is_valid_argcs(int argc, char **argv)
{
	int	i;
	int	nbr;

	i = 1;
	while (i < argc)
	{
		if (!contain_only_digits(argv[i]))
			return (msg(ERROR_DIGITS, argv[i], false));
		nbr = atoi_positive_int(argv[i]);
		if (i == 1 && (nbr <= 0 || nbr > MAX_PHILOS))
			return (msg(ERROR_NBR_PHILOS, STR_MAX_PHILOS, false));
		if (i != 1 && nbr == -1)
			return (msg(ERROR_DIGITS, argv[i], false));
		i++;
	}
	return (true);
}
