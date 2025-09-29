/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:37:40 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/29 04:22:32 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <limits.h>
#include <stdio.h>

int	ft_atoi_remastered(char *str)
{
	int				i;
	unsigned long	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return ((int)nbr);
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->dead_flag)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	check_philo_death(t_data *data)
{
	int			i;
	long long	time;

	i = -1;
	while (++i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		time = get_time() - data->philos[i].last_meal;
		if (time > data->time_to_die)
		{
			pthread_mutex_unlock(&data->data_mutex);
			print_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->death_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->data_mutex);
	}
	return (0);
}
