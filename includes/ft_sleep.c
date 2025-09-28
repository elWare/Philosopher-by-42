/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:03:45 by jumarque          #+#    #+#             */
/*   Updated: 2025/05/27 14:22:33 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_sleeping(t_philo *philo)
{
	ft_status(philo, SLEEPING);
	if (ft_how_are_you(philo) == DIE)
		return (FAILURE);
	ft_writing(philo->data, philo->id, SLEEP);
	ft_delay(ft_get_sleep(philo->data));
	return (SUCCESS);
}

void	ft_sleep_for_eating(t_philo *philo)
{
	ft_delay(ft_get_eat(philo->data));
}
