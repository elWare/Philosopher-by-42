/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:53:21 by jumarque          #+#    #+#             */
/*   Updated: 2025/05/30 09:04:24 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_are_you_dead(void *data_struct)
{
	int		i;
	int		j;
	t_data	*data;
	t_philo	*philos;

	i = -1;
	data = (t_data *)data_struct;
	philos = data->philos;
	j = ft_num_philos(data);
	while (++i < j && ft_keep_or_not(data))
	{
		if (ft_rip(&philos[i]) && ft_keep_or_not(data))
		{
			ft_writing(data, philos[i].id, DIED);
			ft_keep_flag(data, false);
			ft_game_over(data);
			break ;
		}
		if (i == j - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}

t_state	ft_how_are_you(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

int	ft_argv_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (INPUT_ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_error_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (INPUT_ERROR);
	if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200)
		return (INPUT_ERROR);
	while (++i < 5)
	{
		if (ft_atoi(argv[i]) < 60)
			return (INPUT_ERROR);
	}
	return (SUCCESS);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_argv_num(argc, argv) != 0
		|| ft_error_argv(argc, argv))
		return (INPUT_ERROR);
	return (SUCCESS);
}
