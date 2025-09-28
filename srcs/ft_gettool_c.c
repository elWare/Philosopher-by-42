/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettool_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:56:11 by jumarque          #+#    #+#             */
/*   Updated: 2025/05/27 14:12:13 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	ft_get_start(t_data *data)
{
	uint64_t	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}

uint64_t	ft_get_sleep(t_data *data)
{
	uint16_t	time;

	pthread_mutex_lock(&data->mut_sleep_t);
	time = data->sleep_time;
	pthread_mutex_unlock(&data->mut_sleep_t);
	return (time);
}
