/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:03:11 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/17 17:16:59 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->nbr_philos == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time();
	philo->number_of_meals++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		philo_eat(philo);
		if (philo->data->nbr_philos == 1)
			break;
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	all_have_eaten;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	all_have_eaten = 1;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philos[i].number_of_meals < data->must_eat_count)
			all_have_eaten = 0;
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	if (all_have_eaten)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	is_this_the_end(t_data *data)
{
	while (1)
	{
		if (check_philo_death(data) || check_all_ate(data))
			break ;
		usleep(100);
	}
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&routine, &data->philos[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	is_this_the_end(data);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
