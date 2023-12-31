/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:45:51 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/21 18:36:08 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(t_program *program, int time)
{
	long	total_time;

	total_time = ft_get_time() + time;
	while (ft_get_time() < total_time)
	{
		pthread_mutex_lock(&(program->finished));
		if (program->finish != 1)
		{
			pthread_mutex_unlock(&(program->finished));
			usleep(10);
		}
		else
		{
			pthread_mutex_unlock(&(program->finished));
			break ;
		}
	}
}

long	ft_difference_time(t_program *program)
{
	return (ft_get_time() - program->first_timestamp);
}

long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error\nFailed in the function get time of day\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
