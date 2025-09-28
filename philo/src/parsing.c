/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:17:36 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/28 20:56:53 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>
#include <unistd.h>

int	is_it_a_number(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
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
			write(STDOUT_FILENO, "Error: non-digital characters\n", 30);
			return (EXIT_FAILURE);
		}
		nbr = ft_atoi_remastered(av[i]);
		if (nbr < 0)
		{
			write(STDOUT_FILENO, "Error: Number too large\n", 24);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (ft_atoi_remastered(av[1]) == 0 || ft_atoi_remastered(av[1]) > 200)
	{
		write(STDERR_FILENO, "Error: Number of philosophers\n", 30);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
