/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:11:17 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/17 15:53:05 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int room_amount;

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
	printf ("\npath: ");
	if (room.path_index < 0)
		printf("none\n");
	else
		printf ("%d\n", room.path_index);
	printf ("signature: ");
	if(room.path_index == -1)
		printf("start\n");
	else if (room.path_index == -2)
		printf("end\n");
	else
		printf("%d\n", room.signature);
	printf("\n");
}

void	ft_print_farm(t_room *farm)
{
	for (int i = 0; i < room_amount; i++)
		ft_print_room(farm[i]);
}

void	ft_print_signatures(t_room *farm, int depth, int room)
{
	if (farm[room].link_amount <= 1)
		printf("\n");
	for (int i = 0; i < farm[room].link_amount; i++)
	{
		if (farm[farm[room].links[i]].signature != -5)
		{
			printf("%d ", farm[farm[room].links[i]].signature);
			farm[room].signature = -5;
			farm[farm[room].links[i]].signature = -5;
			ft_print_signatures(farm, depth, farm[room].links[i]);
		}
	}
}

int		main(void)
{
	t_room	*farm;
	// int		room_amount;
	int		ant_amount;

	farm = NULL;
	ant_amount = 0;
	room_amount = 0;
	if (!(farm = ft_farm_alloc(farm, &room_amount, &ant_amount)))
		return (1);
	// for (int i = 0; i < room_amount; i++)
	// 	ft_print_room(farm[i]);
	// printf("\n\n");
	ft_ants(farm, ant_amount, room_amount);
	return (0);
}
