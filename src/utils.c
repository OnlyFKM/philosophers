/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:34:34 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/18 17:01:13 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_printf_msg(t_program *program, int id, char *str)
{
	pthread_mutex_lock(&(program->write));
	printf("%lli %d %s\n", (ft_get_time() - program->first_timestamp), id, str);
	pthread_mutex_unlock(&(program->write));
}

int	ft_are_all_digits(const char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		str++;
	}
	return (1);
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
