/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:17:36 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/18 22:45:51 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_it_a_number(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_argument(int ac, char **av)
{
	int	i;
	int	nbr;

	i = 1;
	while (i < ac)
	{
		if (is_it_a_number(av[i]) == EXIT_FAILURE)
		{
			write(STDOUT_FILENO, "non-digital characters\n", 23);
			return (EXIT_FAILURE);
		}
		nbr = ft_atoi_remastered(av[i]);
		if (nbr < 0)
		{
			write(STDOUT_FILENO, "Number too large\n", 17);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
