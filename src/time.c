/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:45:51 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/18 16:52:12 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(int time)
{
	long	total_time;

	total_time = ft_get_time() + time;
	while (ft_get_time() < total_time)
		usleep(10);
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
