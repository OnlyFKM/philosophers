/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:27 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/20 14:58:37 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_integers(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_are_all_digits(argv[i]) == EXIT_FAILURE)
		{
			printf("Error\nArgues must be positive integers\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atol(argv[i]) > INT_MAX)
		{
			printf("Error\nAn integer is too high\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_program	program;

	if (argc == 5 || argc == 6)
	{
		if (ft_check_integers(argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_init_all(&program, argc, argv) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_philosopher(&program) == EXIT_FAILURE)
			return (printf("Error\nFailure creating threads\n"), EXIT_FAILURE);
	}
	else
		return (printf("Error\nWrong number of argues\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
