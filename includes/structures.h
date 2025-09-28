/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:33:01 by jumarque          #+#    #+#             */
/*   Updated: 2025/05/22 18:33:06 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum s_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DIE = 3,
	FULL = 4,
	OFF = 5
}	t_state;

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	mut_last_eat;
	pthread_mutex_t	mut_num_meals;
	pthread_mutex_t	mut_state;
	struct s_data	*data;
	t_state			state;
	uint64_t		last_eat;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;			
	int				nb_meals;			
	int				nb_full_p;			
	bool			keep_iterating;
	uint64_t		eat_time;
	uint64_t		die_time;				
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	mut_eat_t;
	pthread_mutex_t	mut_die_t;				
	pthread_mutex_t	mut_sleep_t;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_nb_philos;
	pthread_mutex_t	mut_keep_iter;
	pthread_mutex_t	mut_start_time;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

#endif