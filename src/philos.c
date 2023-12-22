/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:13:07 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/22 13:49:02 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_philos(t_program *program, pthread_t *threads)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < program->number_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	while (j < program->number_philos)
	{
		pthread_mutex_destroy((&(program->forks[j])));
		j++;
	}
	pthread_mutex_destroy((&(program->meal_mutex)));
	pthread_mutex_destroy((&(program->write)));
	pthread_mutex_destroy((&(program->finished)));
	pthread_mutex_destroy((&(program->time)));
	pthread_mutex_destroy((&(program->meal)));
}

void	ft_one_philo(t_program *program, pthread_t *threads)
{
	pthread_mutex_lock(&(program->forks[program->philo[0].left_fork_id]));
	ft_printf_msg(program, program->philo[0].philo_id, "has taken a fork");
	ft_usleep(program, program->time_death);
	pthread_mutex_unlock(&(program->forks[program->philo[0].left_fork_id]));
	ft_printf_msg(program, program->philo[0].philo_id, "died");
	ft_free_philos(program, threads);
}

int	ft_check_if_dead(t_program *program)
{
	long		death_time;
	long		difference;

	death_time = program->time_death;
	pthread_mutex_lock(&(program->time));
	difference = ft_get_time() - program->philo->time_last_meal;
	pthread_mutex_unlock(&(program->time));
	if (difference >= death_time)
	{
		ft_printf_msg(program, program->philo->philo_id, "died");
		pthread_mutex_lock(&(program->finished));
		program->finish = 1;
		pthread_mutex_unlock(&(program->finished));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_philosopher(t_program *program)
{
	int			i;
	pthread_t	*threads;

	i = -1;
	threads = malloc(sizeof(pthread_t) * program->number_philos);
	pthread_mutex_lock(&(program->time));
	program->first_timestamp = ft_get_time();
	pthread_mutex_unlock(&(program->time));
	while ((++i < program->number_philos) && (program->number_philos > 1))
	{
		if (pthread_create(&(threads[i]), NULL, ft_routine,
				&(program->philo[i])))
			return (EXIT_FAILURE);
		pthread_mutex_lock(&(program->time));
		program->philo[i].time_last_meal = ft_get_time();
		pthread_mutex_unlock(&(program->time));
	}
	if (program->number_philos == 1)
		return (ft_one_philo(program, threads), EXIT_SUCCESS);
	while (1)
	{
		ft_check_if_dead(program);
		if (ft_check_finish(program) == EXIT_FAILURE)
			break ;
	}
	ft_free_philos(program, threads);
	free(threads);
	return (EXIT_SUCCESS);
}
