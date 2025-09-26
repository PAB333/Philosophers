/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:07:34 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/26 18:07:59 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	assign_forks(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s)
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
