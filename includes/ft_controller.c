/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:16:20 by jumarque          #+#    #+#             */
/*   Updated: 2025/06/02 09:29:34 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_keep_or_not(t_data *data)
{
	bool	keep;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep);
}

bool	ft_has_eaten(t_data *data, t_philo *philo)
{
	bool	res;

	res = false;
	if (ft_times_eating(philo) >= data->nb_meals)
		res = true;
	return (res);
}

bool	ft_rip(t_philo *philo)
{
	bool	res;
	t_data	*data;

	data = philo->data;
	res = false;
	if (ft_my_watch() - ft_get_last_eat(philo) > ft_get_die(data)
		&& ft_how_are_you(philo) != EATING)
	{
		ft_status(philo, DIE);
		res = true;
	}
	return (res);
}

bool	ft_num_meals(t_data	*data)
{
	if (data->nb_meals > 0)
		return (true);
	return (false);
}
