/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:43:10 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/19 12:16:29 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_init_philo(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->number_philos)
	{
		program->philo[i].philo_id = i + 1;
		program->philo[i].left_fork_id = i;
		program->philo[i].right_fork_id = (i + 1) % program->number_philos;
		program->philo[i].times_philo_has_eaten = 0;
		program->philo[i].time_last_meal = 0;
		program->philo[i].program = program;
		i++;
	}
}

int	ft_init_mutex(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->number_philos)
	{
		if (pthread_mutex_init(&(program->forks[i]), NULL))
			return (printf("Error\nMutex initialization failed for forks"),
				EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_init(&(program->write), NULL))
		return (printf("Error\nMutex initialization failed for write\n"),
			EXIT_FAILURE);
	if (pthread_mutex_init(&(program->meal_mutex), NULL))
		return (printf("Error\nMutex initialization failed for meal\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_check_init(t_program *program, int argc)
{
	if (program->number_philos <= 0)
		return (printf("Error\nWrong number of philosophers\n"), EXIT_FAILURE);
	if (program->time_death <= 0)
		return (printf("Error\nWrong time to die\n"), EXIT_FAILURE);
	if (program->time_eat <= 0)
		return (printf("Error\nWrong time to eat\n"), EXIT_FAILURE);
	if (program->time_sleep <= 0)
		return (printf("Error\nWrong time to sleep\n"), EXIT_FAILURE);
	if (argc == 6)
	{
		if (program->number_meals <= 0)
			return (printf("Error\nWrong number of meals\n"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_init_argues(t_program *program, int argc, char *argv[])
{
	program->number_philos = ft_atol(argv[1]);
	program->time_death = ft_atol(argv[2]);
	program->time_eat = ft_atol(argv[3]);
	program->time_sleep = ft_atol(argv[4]);
	if (argc == 5)
		program->number_meals = -1;
	if (argc == 6)
		program->number_meals = ft_atol(argv[5]);
}

int	ft_init_all(t_program *program, int argc, char *argv[])
{
	ft_init_argues(program, argc, argv);
	if (ft_check_init(program, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_init_philo(program);
	ft_init_mutex(program);
	return (0);
}
