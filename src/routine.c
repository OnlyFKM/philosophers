/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:40:22 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/22 13:50:15 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_all_eat(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&(program->meal_mutex));
	if (philo->times_philo_has_eaten == program->number_meals)
	{
		pthread_mutex_lock(&(program->time));
		program->all_philos_have_eaten++;
		pthread_mutex_unlock(&(program->time));
	}
	pthread_mutex_unlock(&(program->meal_mutex));
	pthread_mutex_lock(&(program->time));
	if (program->all_philos_have_eaten == program->number_philos)
	{
		pthread_mutex_lock(&(program->finished));
		program->finish = 1;
		pthread_mutex_unlock(&(program->finished));
		pthread_mutex_unlock(&(program->time));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(program->time));
	return (EXIT_SUCCESS);
}

void	ft_eating(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&(program->forks[philo->left_fork_id]));
	ft_printf_msg(program, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(program->forks[philo->right_fork_id]));
	ft_printf_msg(program, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(program->meal_mutex));
	ft_printf_msg(program, philo->philo_id, "is eating");
	pthread_mutex_lock(&(program->time));
	philo->time_last_meal = ft_get_time();
	pthread_mutex_unlock(&(program->time));
	philo->times_philo_has_eaten++;
	pthread_mutex_unlock(&(program->meal_mutex));
	ft_check_all_eat(philo);
	ft_usleep(program, program->time_eat);
	pthread_mutex_unlock(&(program->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(program->forks[philo->right_fork_id]));
}

void	*ft_routine(void *arg)
{
	t_program	*program;
	t_philo		*philo;

	philo = (t_philo *)arg;
	program = philo->program;
	if (philo->philo_id % 2)
		ft_usleep(program, 10);
	while (1)
	{
		ft_eating(philo);
		if (ft_check_finish(program) == EXIT_FAILURE)
			break ;
		ft_printf_msg(program, philo->philo_id, "is sleeping");
		ft_usleep(program, program->time_sleep);
		if (ft_check_finish(program) == EXIT_FAILURE)
			break ;
		ft_printf_msg(program, philo->philo_id, "is thinking");
		if (ft_check_finish(program) == EXIT_FAILURE)
			break ;
	}
	return (NULL);
}
