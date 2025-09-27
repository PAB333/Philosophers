/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibreiss <pibreiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:48:38 by pibreiss          #+#    #+#             */
/*   Updated: 2025/09/27 17:54:33 by pibreiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	bool			is_taken;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				number_of_meals;
	long long		last_meal;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
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
	int				initialized_forks;
	long long		start_time;
	t_fork			*forks;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	start_mutex;
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
void		destroy_mutex_init(t_data *data, int nb_forks);

// simulation_and_fork_util
void		assign_forks(t_philo *p, t_fork **f, t_fork **s);
void		single_philo(t_philo *philo, t_fork *fork);
int			check_all_ate(t_data *data);
void		is_this_the_end(t_data *data);

#endif