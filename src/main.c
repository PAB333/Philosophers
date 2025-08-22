/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:48:10 by pibreiss          #+#    #+#             */
/*   Updated: 2025/08/20 02:23:26 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		write(STDOUT_FILENO, "Error: Incorrect number of arguments\n", 30);
		return (EXIT_FAILURE);
	}
	if (!check_argument(ac, av))
		return (EXIT_FAILURE);
	if (init_data(&data, ac, av) == EXIT_FAILURE)
	{
		write(STDOUT_FILENO, "Error: Initialization failed\n", 22);
		//free_all
		return (EXIT_FAILURE);
	}
	if (start_simulation(&data) == EXIT_FAILURE)
	{
		write(STDOUT_FILENO, "Error: Simulation failed\n", 25);
		//free_all
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
