/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:37:40 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/27 17:54:26 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <sys/time.h>
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

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;
	int			is_dead_flag;

	pthread_mutex_lock(&philo->data->death_mutex);
	is_dead_flag = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_dead_flag)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
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

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		time = get_time() - data->philos[i].last_meal;
		pthread_mutex_unlock(&data->data_mutex);
		if (time >= data->time_to_die)
		{
			print_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->death_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
