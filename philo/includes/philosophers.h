/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:48:38 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/17 16:32:29 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				number_of_meals;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead_flag;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

// parsing
int			check_argument(int ac, char **av);

// initialization
int			init_data(t_data *data, int ac, char **av);

// simulation
int			start_simulation(t_data *data);

// utils
int			ft_atoi_remastered(char *str);
long long	get_time(void);
void		print_status(t_philo *philo, char *status);
int			is_dead(t_philo *philo);
int			check_philo_death(t_data *data);

// free_utils
void		free_all(t_data *data);
void		*ft_memset(void *s, int c, size_t n);

#endif