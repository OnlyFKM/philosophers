/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:13:07 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/20 13:24:44 by frcastil         ###   ########.fr       */
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
		pthread_mutex_destroy((&(program->forks[j])));
		j++;
	}
	pthread_mutex_destroy((&(program->meal_mutex)));
	pthread_mutex_destroy((&(program->write)));
}

void	ft_one_philo(t_program *program)
{
	pthread_mutex_lock(&(program->forks[program->philo[0].left_fork_id]));
	ft_printf_msg(program, program->philo[0].philo_id, "has taken a fork");
	ft_usleep(program, program->time_death);
	pthread_mutex_unlock(&(program->forks[program->philo[0].left_fork_id]));
	ft_printf_msg(program, program->philo[0].philo_id, "died");
	ft_free_philos(program);
}

int	ft_check_if_dead(t_program *program)
{
	long		death_time;
	long		difference;

	death_time = program->time_death;
	difference = ft_get_time() - program->philo->time_last_meal;
	if (difference >= death_time)
	{
		ft_printf_msg(program, program->philo->philo_id, "died");
		program->finish = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_philosopher(t_program *program)
{
	int		i;

	i = 0;
	program->first_timestamp = ft_get_time();
	while ((i < program->number_philos) && (program->number_philos > 1))
	{
		if (pthread_create(&(program->philo[i].thread_id), NULL, ft_routine,
				&(program->philo[i])))
			return (EXIT_FAILURE);
		program->philo[i].time_last_meal = ft_get_time();
		i++;
	}
	if (program->number_philos == 1)
		ft_one_philo(program);
	while (1)
	{
		ft_check_if_dead(program);
		if (program->finish == 1)
			break ;
	}
	ft_free_philos(program);
	return (EXIT_SUCCESS);
}
