/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:55:02 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/29 03:45:47 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		return (EXIT_FAILURE);
	while (i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].number_of_meals = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nbr_philos];
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		destroy_mutex_init(data, data->nbr_philos);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		destroy_mutex_init(data, -1);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		destroy_mutex_init(data, -2);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
	{
		destroy_mutex_init(data, -3);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->nbr_philos);
	if (!data->forks)
		return (EXIT_FAILURE);
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->forks[i].fork_mutex, NULL) != 0)
		{
			destroy_mutex_init(data, i);
			free(data->forks);
			data->forks = NULL;
			return (EXIT_FAILURE);
		}
		data->forks[i].is_taken = false;
		i++;
	}
	data->initialized_forks = i;
	if (init_data_mutex(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nbr_philos = ft_atoi_remastered(av[1]);
	data->time_to_die = ft_atoi_remastered(av[2]);
	data->time_to_eat = ft_atoi_remastered(av[3]);
	data->time_to_sleep = ft_atoi_remastered(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atoi_remastered(av[5]);
	else
		data->must_eat_count = -1;
	data->dead_flag = 0;
	data->initialized_forks = 0;
	if (init_fork(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
