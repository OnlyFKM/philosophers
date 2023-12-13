/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:13:07 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/13 18:26:02 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_sleeping(t_program *program)
{
	(void) program;
	printf("Aqui estoy\n");
}

void	ft_eating(t_program *program)
{
	pthread_mutex_lock(&(program->philo->left_fork_id));
	ft_printf_msg(program, program->philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(program->philo->right_fork_id));
	ft_printf_msg(program, program->philo->philo_id, "has taken a fork");
	ft_printf_msg(program, program->philo->philo_id, "is eating");
	usleep(program->time_eat * 1000);
	pthread_mutex_unlock(&(program->philo->left_fork_id));
	pthread_mutex_unlock(&(program->philo->right_fork_id));
}

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

void	ft_routine(void)
{
	t_program	*program;

	if (!(program->philo->philo_id % 2))
		usleep(15000);
	while (1)
	{
		ft_eating(program);
		ft_printf_msg(program, program->philo->philo_id, "is sleeping");
		ft_sleeping(program);
		ft_printf_msg(program, program->philo->philo_id, "is thinking");
		if (program->all_philos_have_eaten || program->philo_died)
			break ;
	}
}

void	ft_one_philo(t_program *program)
{
	pthread_mutex_lock(&(program->philo->left_fork_id));
	ft_printf_msg(program, program->number_philos, "has taken a fork");
	ft_sleeping(program);
	pthread_mutex_unlock(&(program->philo->left_fork_id));
	ft_printf_msg(program, program->philo->philo_id, "has died");
	ft_free_philos(program);
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
