/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:27 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/02 18:45:03 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



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
	int			i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		if (ft_check_integers(argv) == -1)
			return (EXIT_FAILURE);
		ft_init_all(&program, argc, argv);
	}
	else
		return (printf("Error\nWrong number of argues\n"), EXIT_FAILURE);
	return (0);
}
