/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcastil <frcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:42:15 by frcastil          #+#    #+#             */
/*   Updated: 2023/12/22 13:52:12 by frcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

struct	s_program;

typedef struct s_philos
{
	struct s_program	*program;
	int					philo_id;
	int					left_fork_id;
	int					right_fork_id;
	int					times_philo_has_eaten;
	long long			time_last_meal;
}	t_philo;

typedef struct s_program
{
	int				number_philos;
	int				time_death;
	int				time_sleep;
	int				time_eat;
	int				number_meals;
	int				all_philos_have_eaten;
	int				finish;
	long long		first_timestamp;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	write;
	pthread_mutex_t	finished;
	pthread_mutex_t	meal;
	pthread_mutex_t	time;
	t_philo			philo[250];
}	t_program;

// main.c
int			main(int argc, char *argv[]);
int			ft_check_integers(char *argv[]);

// utils.c
int			ft_are_all_digits(const char *str);
long long	ft_atol(const char *str);
void		ft_printf_msg(t_program *program, int id, char *str);
int			ft_check_finish(t_program *program);

// init.c
int			ft_init_all(t_program *program, int argc, char *argv[]);
void		ft_init_argues(t_program *program, int argc, char *argv[]);
int			ft_check_init(t_program *program, int argc);
int			ft_init_mutex(t_program *program);
void		ft_init_philo(t_program *program);

// philos.c
int			ft_philosopher(t_program *program);
void		ft_one_philo(t_program *program, pthread_t *threads);
void		ft_free_philos(t_program *program, pthread_t *threads);
int			ft_check_if_dead(t_program *program);

// routine.c
void		*ft_routine(void *arg);
void		ft_eating(t_philo *philo);

// time.c
long		ft_get_time(void);
long		ft_difference_time(t_program *program);
void		ft_usleep(t_program *program, int time);

#endif