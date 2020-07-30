/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:11:17 by vkuikka           #+#    #+#             */
/*   Updated: 2020/07/30 15:11:18 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h>

void	ft_error(char *message)
{
	ft_putstr("error: ");
	ft_putstr(message);
	exit(1);
}

int		main(void)
{
	t_room	*farm;
	char	**ant_names;
	int		room_amount;
	int		ant_amount;

	farm = NULL;
	ant_names = NULL;
	ant_amount = 0;
	room_amount = 0;
	if (!(farm = ft_farm_alloc(farm, ant_names, &room_amount, &ant_amount)))
		return (1);
	printf("\n\nroom amount: %d\n", room_amount);
	return (0);
}