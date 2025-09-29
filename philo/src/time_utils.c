/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 23:33:13 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/29 01:44:04 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <sys/time.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time, t_data *data)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (is_dead(data->philos))
			break ;
		usleep(50);
	}
}
