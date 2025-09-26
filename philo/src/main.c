/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:48:10 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/26 17:59:16 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		write(STDOUT_FILENO, "Error: Incorrect number of arguments\n", 37);
		return (EXIT_FAILURE);
	}
	if (check_argument(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_memset(&data, 0, sizeof(t_data));
	if (init_data(&data, ac, av) == EXIT_FAILURE)
	{
		write(STDOUT_FILENO, "Error: Initialization failed\n", 29);
		return (EXIT_FAILURE);
	}
	if (start_simulation(&data) == EXIT_FAILURE)
	{
		write(STDOUT_FILENO, "Error: Simulation failed\n", 25);
		free_all(&data);
		return (EXIT_FAILURE);
	}
	free_all(&data);
	return (EXIT_SUCCESS);
}
