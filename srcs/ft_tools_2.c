/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:26:49 by jumarque          #+#    #+#             */
/*   Updated: 2025/06/02 09:31:10 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_num_philos(t_data *data)
{
	int	nb_philos;

	pthread_mutex_lock(&data->mut_nb_philos);
	nb_philos = data->nb_philos;
	pthread_mutex_unlock(&data->mut_nb_philos);
	return (nb_philos);
}

void	ft_game_over(t_data *data)
{
	int		i;
	int		j;
	t_philo	*philos;

	i = -1;
	j = ft_num_philos(data);
	philos = data->philos;
	while (++i < j)
		ft_status(&philos[i], DIE);
}

void	ft_status(t_philo *philo, t_state status)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DIE)
		philo->state = status;
	pthread_mutex_unlock(&philo->mut_state);
}

void	ft_keep_flag(t_data *value, bool now)
{
	pthread_mutex_lock(&value->mut_keep_iter);
	value->keep_iterating = now;
	pthread_mutex_unlock(&value->mut_keep_iter);
}
