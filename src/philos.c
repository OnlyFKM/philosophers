/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:13:07 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/13 19:52:33 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_philos(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < program->number_philos)
	{
		pthread_join(program->philo[i].thread_id, NULL);
		i++;
	}
	while (j < program->number_philos)
	{
		pthread_mutex_destroy((&(program->forks[i])));
		j++;
	}
	pthread_mutex_destroy((&(program->meal_mutex)));
	pthread_mutex_destroy((&(program->write)));
}

void	ft_one_philo(t_program *program)
{
	pthread_mutex_lock(&(program->forks[program->philo->left_fork_id]));
	ft_printf_msg(program, program->number_philos, "has taken a fork");
	ft_sleeping(program);
	pthread_mutex_unlock(&(program->forks[program->philo->left_fork_id]));
	ft_printf_msg(program, program->philo->philo_id, "has died");
	ft_free_philos(program);
}

void	ft_check_if_dead(t_program *program)
{
	ft_printf_msg(program, program->philo->philo_id, "died");
	program->philo_died = 1;
}

int	ft_philosopher(t_program *program)
{
	t_philo	*philo;
	int		i;

	philo = program->philo;
	i = 0;
	program->first_timestamp = ft_get_time();
	while ((i < program->number_philos) && (program->number_philos > 1))
	{
		if (pthread_create(&(philo[i].thread_id), NULL, ft_routine,
				&(philo[i])))
			return (-1);
		philo[i].time_last_meal = ft_get_time();
		i++;
	}
	if (program->number_philos == 1)
		ft_one_philo(program);
	ft_free_philos(program);
	return (1);
}
