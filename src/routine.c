/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:40:22 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/19 12:05:50 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_check_all_eat(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	if (philo->times_philo_has_eaten == program->number_meals)
		program->all_philos_have_eaten++;
	if (program->all_philos_have_eaten == program->number_philos)
		exit (EXIT_FAILURE);
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
	philo->time_last_meal = ft_get_time();
	pthread_mutex_unlock(&(program->meal_mutex));
	philo->times_philo_has_eaten++;
	ft_check_all_eat(philo);
	ft_usleep(program->time_eat);
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
		ft_usleep(100);
	while (program->philo_died != 1)
	{
		ft_eating(philo);
		ft_check_if_dead(program);
		/* if (program->all_philos_have_eaten == 1)
			return (NULL); */
		ft_printf_msg(program, philo->philo_id, "is sleeping");
		ft_usleep(program->time_sleep);
		/* if (program->all_philos_have_eaten == 1)
			return (NULL); */
		ft_printf_msg(program, philo->philo_id, "is thinking");
		/* if (program->all_philos_have_eaten == 1)
			return (NULL); */
	}
	return (NULL);
}
