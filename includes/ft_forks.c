/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:45:39 by jumarque          #+#    #+#             */
/*   Updated: 2025/06/10 15:13:52 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_drop_fork(t_philo *philo)
{
	ft_drop_fork_r(philo);
	ft_drop_fork_l(philo);
}

void	ft_drop_fork_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
}

void	ft_drop_fork_r(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_r);
}
