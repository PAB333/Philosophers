/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:03:11 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/27 17:57:20 by pibreiss         ###   ########.fr       */
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
	pthread_mutex_lock(&first_fork->fork_mutex);
	first_fork->is_taken = true;
	print_status(philo, "has taken a fork");
	if (philo->data->nbr_philos == 1)
	{
		single_philo(philo, first_fork);
		return ;
	}
	pthread_mutex_lock(&second_fork->fork_mutex);
	second_fork->is_taken = true;
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal = get_time();
	philo->number_of_meals++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	usleep(philo->data->time_to_eat * 1000);
	second_fork->is_taken = false;
	pthread_mutex_unlock(&second_fork->fork_mutex);
	first_fork->is_taken = false;
	pthread_mutex_unlock(&first_fork->fork_mutex);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		philo_eat(philo);
		if (philo->data->nbr_philos == 1)
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
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
