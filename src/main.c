/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:27 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/04 17:12:54 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		printf("my id: %d\n", philo->philo_id);
	}
	return (NULL);
}

int	ft_check_integers(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_are_all_digits(argv[i++]) == -1)
			return (printf("Error\nArgues must be positive integers\n"), -1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atol(argv[i]) > INT_MAX)
			return (printf("Error\nAn integer is too high\n"), -1);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_program	program;

	if (argc == 5 || argc == 6)
	{
		if (ft_check_integers(argv) == -1)
			return (EXIT_FAILURE);
		ft_init_all(&program, argc, argv);
		pthread_create(&program.philo[0].thread_id, NULL, ft_routine,
			&program.philo[0]);
		pthread_join(program.philo[0].thread_id, NULL);
	}
	else
		return (printf("Error\nWrong number of argues\n"), EXIT_FAILURE);
	return (0);
}
