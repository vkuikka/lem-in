/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:11:17 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/28 15:51:00 by vkuikka          ###   ########.fr       */
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

void	ft_print_room(t_room room)
{
	printf("name: %s\n", room.room_name);
	printf("links: ");
	for (int i = 0; i < room.link_amount; i++)
		printf("%d ", room.links[i]);
	printf ("  total: %d", room.link_amount);
	printf ("\nant: ");
	if (room.ant_index < 0)
		printf("none\n");
	else
		printf ("%d\n", room.ant_index);
	printf ("signature: ");
	if(room.signature == -1)
		printf("start\n");
	else if (room.signature == -2)
		printf("end\n");
	else
		printf("%d\n", room.signature);
	printf("\n");
}

int		main(void)
{
	t_room	*farm;
	int		room_amount;
	int		ant_amount;

	farm = NULL;
	ant_amount = 0;
	room_amount = 0;
	if (!(farm = ft_farm_alloc(farm, &room_amount, &ant_amount)))
		return (1);
	for (int i = 0; i < room_amount; i++)
		ft_print_room(farm[i]);
	printf("\n\n");
	
	ft_ants(farm, ant_amount, room_amount);
	exit(1);

	for (int i = 0; i < room_amount; i++)
		ft_print_room(farm[i]);
	printf("\nroom amount: %d", room_amount);
	printf("\nant  amount: %d\n\n", ant_amount);
	return (0);
}