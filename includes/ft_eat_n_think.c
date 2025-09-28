/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_n_think.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:44:47 by jumarque          #+#    #+#             */
/*   Updated: 2025/05/31 19:31:30 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_times_eating(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->mut_num_meals);
	res = philo->meals;
	pthread_mutex_unlock(&philo->mut_num_meals);
	return (res);
}

int	ft_eating(t_philo *philo)
{
	if (ft_get_forks(philo) != 0)
		return (FAILURE);
	ft_status(philo, EATING);
	if (!ft_has_eaten(philo->data, philo) || philo->data->nb_meals == -1)
		ft_writing(philo->data, philo->id, EAT);
	ft_get_last_meal(philo);
	ft_sleep_for_eating(philo);
	ft_get_num_meals(philo);
	ft_drop_fork(philo);
	return (SUCCESS);
}

int	ft_thinking(t_philo *philo)
{
	ft_status(philo, THINKING);
	if (ft_how_are_you(philo) == DIE)
		return (FAILURE);
	ft_writing(philo->data, philo->id, THINK);
	return (SUCCESS);
}
