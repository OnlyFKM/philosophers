/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:40:22 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/14 17:16:56 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eating(t_program *program)
{
	pthread_mutex_lock(&(program->forks[program->philo->left_fork_id]));
	ft_printf_msg(program, program->philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(program->forks[program->philo->right_fork_id]));
	ft_printf_msg(program, program->philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(program->meal_mutex));
	ft_printf_msg(program, program->philo->philo_id, "is eating");
	pthread_mutex_unlock(&(program->meal_mutex));
	usleep(program->time_eat * 1000);
	pthread_mutex_unlock(&(program->forks[program->philo->left_fork_id]));
	pthread_mutex_unlock(&(program->forks[program->philo->right_fork_id]));
}

void	*ft_routine(void *arg)
{
	t_program	*program;
	t_philo		*philo;

	philo = (t_philo *)arg;
	program = philo->program;
	if (!(program->philo->philo_id % 2))
		usleep(15000);
	while (1)
	{
		ft_eating(program);
		ft_printf_msg(program, program->philo->philo_id, "is sleeping");
		ft_usleep(program->time_sleep);
		ft_printf_msg(program, program->philo->philo_id, "is thinking");
		if (program->all_philos_have_eaten || program->philo_died)
			break ;
	}
	return (NULL);
}
