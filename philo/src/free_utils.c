/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:13:55 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/27 17:54:40 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->initialized_forks)
		{
			pthread_mutex_destroy(&data->forks[i].fork_mutex);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	if (data->philos)
		free(data->philos);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void	destroy_mutex_init(t_data *data, int nb_forks)
{
	int	i;

	i = 0;
	while (i < nb_forks)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		i++;
	}
	if (nb_forks <= -1)
		pthread_mutex_destroy(&data->print_mutex);
	if (nb_forks <= -2)
		pthread_mutex_destroy(&data->death_mutex);
	if (nb_forks == -3)
		pthread_mutex_destroy(&data->data_mutex);
}
