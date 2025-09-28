/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:00:08 by jumarque          #+#    #+#             */
/*   Updated: 2025/06/02 09:30:48 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_delay(uint64_t pause)
{
	uint64_t	ini;

	ini = ft_my_watch();
	while ((ft_my_watch() - ini) < pause)
		usleep(500);
}

uint64_t	ft_my_watch(void)
{
	struct timeval	ms;

	if (gettimeofday(&ms, NULL))
		return (SUCCESS);
	return (ms.tv_sec * (uint64_t)1000 + (ms.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str [i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}
