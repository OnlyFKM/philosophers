/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:34:34 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/21 11:36:25 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_printf_msg(t_program *program, int id, char *str)
{
	long long	time;

	time = ft_get_time() - program->first_timestamp;
	if (program->finish != 1)
	{
		pthread_mutex_lock(&(program->write));
		printf("%lli %d %s\n", time, id, str);
		pthread_mutex_unlock(&(program->write));
	}
	else
		ft_free_philos(program);
}

int	ft_are_all_digits(const char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (EXIT_FAILURE);
		str++;
	}
	return (EXIT_SUCCESS);
}

long long	ft_atol(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
		if (*str == '+' || *str == '-')
			return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
