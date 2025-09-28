/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettool_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:48:45 by jumarque          #+#    #+#             */
/*   Updated: 2025/06/10 15:50:18 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_get_fork_l(t_philo *philo)
{
	if (ft_rip(philo) || ft_how_are_you(philo) == DIE)
		return (FAILURE);
	pthread_mutex_lock(philo->fork_l);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}

int	ft_get_fork_r(t_philo *philo)
{
	if (ft_rip(philo) || ft_how_are_you(philo) == DIE)
		return (FAILURE);
	pthread_mutex_lock(philo->fork_r);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}

int	ft_get_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (ft_num_philos(philo->data) == 1)
		return (ft_only_one(philo));
	if (philo->fork_l < philo->fork_r)
	{
		first = philo->fork_l;
		second = philo->fork_r;
	}
	else
	{
		first = philo->fork_r;
		second = philo->fork_l;
	}
	pthread_mutex_lock(first);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	pthread_mutex_lock(second);
	ft_writing(philo->data, philo->id, TAKE_FORKS);
	return (SUCCESS);
}
