/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seciurte <seciurte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:35:51 by seciurte          #+#    #+#             */
/*   Updated: 2022/01/19 18:38:35 by seciurte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	terminate(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_rules->mtx);
	if (philo->sim_rules->stop == 1)
	{
		pthread_mutex_unlock(&philo->sim_rules->mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim_rules->mtx);
	return (0);
}

void	*start_work(void *arg)
{
	t_philo				*philo;

	philo = (t_philo *)arg;
	while (philo->nb_of_cycles && !terminate(philo))
	{
		if (!terminate(philo))
		{
			philo->last_meal = philo_eat(philo);
			if (philo->last_meal == -1)
				return (NULL);
		}
		if (!terminate(philo) && philo->nb_of_cycles - 1)
			philo_sleep(philo);
		if (philo->nb_of_cycles > 0)
			philo->nb_of_cycles--;
	}
	return (NULL);
}
