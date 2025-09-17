/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:55:02 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/17 16:26:52 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->forks)
		return (EXIT_FAILURE);
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->print_mutex);
		free(data->forks);
		return (EXIT_FAILURE);
	}
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
	data->start_time = get_time();
	if (init_fork(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(data) == EXIT_FAILURE)
	{
		free_all(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
