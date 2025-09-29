/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:03:11 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/29 02:00:03 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>
#include <unistd.h>

void	philo_eat(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	assign_forks(philo, &first_fork, &second_fork);
	take_fork(first_fork, philo);
	if (philo->data->nbr_philos == 1)
	{
		ft_usleep(philo->data->time_to_die, philo->data);
		release_fork(first_fork);
		return ;
	}
	take_fork(second_fork, philo);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal = get_time();
	philo->number_of_meals++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	release_fork(second_fork);
	release_fork(first_fork);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(philo))
	{
		print_status(philo, "is thinking");
		philo_eat(philo);
		if (philo->data->nbr_philos == 1)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}

int	join_threads(t_data *data, int created_threads, int status)
{
	int	i;

	i = 0;
	if (status == 1)
	{
		while (i < created_threads + 1)
		{
			pthread_join(data->philos[i].thread_id, NULL);
			i++;
		}
	}
	if (status == 2)
	{
		while (i < data->nbr_philos)
		{
			pthread_join(data->philos[i].thread_id, NULL);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start_mutex);
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&routine, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_unlock(&data->start_mutex);
			join_threads(data, i, 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	start_simulation(t_data *data)
{
	int	i;

	if (create_threads(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	data->start_time = get_time();
	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	pthread_mutex_unlock(&data->start_mutex);
	is_this_the_end(data);
	join_threads(data, data->nbr_philos, 2);
	return (EXIT_SUCCESS);
}
