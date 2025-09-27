/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_and_fork_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:07:34 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/27 20:34:34 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <unistd.h>

void	assign_forks(t_philo *p, t_fork **f, t_fork **s)
{
	if (p->id % 2 == 0)
	{
		*f = p->left_fork;
		*s = p->right_fork;
	}
	else
	{
		*f = p->right_fork;
		*s = p->left_fork;
	}
}

void	single_philo(t_philo *philo, t_fork *fork)
{
	usleep(philo->data->time_to_die * 1000);
	fork->is_taken = false;
	pthread_mutex_unlock(&fork->fork_mutex);
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
		pthread_mutex_lock(&data->data_mutex);
		if (data->philos[i].number_of_meals < data->must_eat_count)
			all_have_eaten = 0;
		pthread_mutex_unlock(&data->data_mutex);
		if (!all_have_eaten)
			break ;
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
