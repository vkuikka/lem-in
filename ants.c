/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:23:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/26 15:30:53 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	ft_find_endpoint(t_room *farm, int room_amount, int path_index)
{
	int		i;

	i = 0;
	while (i < room_amount)
	{
		if (farm[i].path_index == path_index)
			return (i);
		i++;
	}
	printf("error: room not found fix me now\n");
	exit(1);
	return (-1);
}

static int	ft_map_farm(t_room *farm, int room)
{
	int		bad_links;
	int		i;

	if (farm[room].link_amount < 2 && farm[room].signature > -1)
	{
		farm[room].signature = -1;
		return (0);
	}
	i = 0;
	bad_links = 0;
	while (i < farm[room].link_amount)
	{
		if (farm[farm[room].links[i]].path_index == -2)
		{
			//gives last room a signature
			if (farm[room].signature + 1 < farm[farm[room].links[i]].signature ||
				!farm[farm[room].links[i]].signature)
				farm[farm[room].links[i]].signature = farm[room].signature + 1;
			return (1);
		}
		if (farm[farm[room].links[i]].signature == -1)
			bad_links++;
		else if (farm[farm[room].links[i]].path_index != -1 &&
				(farm[farm[room].links[i]].signature == 0 ||
				farm[farm[room].links[i]].signature > farm[room].signature + 1))
		{
			farm[farm[room].links[i]].signature = farm[room].signature + 1;
			if (!(ft_map_farm(farm, farm[room].links[i])))
				bad_links++;
		}
		i++;
	}
	if (i - bad_links <= 1)
	{
		farm[room].signature = -1;
		return (0);
	}
	return (1);
}

/*
**	signatures:
**		-1 dead end
**		0 not visited
**		0 < distance from start
**
**	path_indices:
**		-2 end
**		-1 start
**		0 not visited
**		0 < path index
*/

void		ft_ants(t_room *farm, int ant_amount, int room_amount)
{
	// int		**paths;
	int		path_amount;
	int		start_index;
	int		exit_index;

	start_index = ft_find_endpoint(farm, room_amount, -1);
	exit_index = ft_find_endpoint(farm, room_amount, -2);
	path_amount = farm[start_index].link_amount < farm[exit_index].link_amount ?
				farm[start_index].link_amount : farm[exit_index].link_amount;
	// if (!(paths = (int **)malloc(sizeof(int *) * path_amount)))
	// 	ft_error("memory allocation failed");
	// room = 0;
	// while (room < path_amount)
	// {
	// 	if (!(paths[room] = (int *)malloc(sizeof(int) * room_amount)))
	// 		ft_error("memory allocation failed");
	// 	ft_memset(paths[room], -1, room_amount * 4);
	// 	room++;
	// }
	printf("start links: ");
	for (int i = 0; i < farm[start_index].link_amount; i++)
		printf("%d ", farm[start_index].links[i]);
	printf("\nend links: ");
	for (int i = 0; i < farm[exit_index].link_amount; i++)
		printf("%d ", farm[exit_index].links[i]);
	printf("\n");

	printf("%d %d\n", start_index, exit_index);

	ft_map_farm(farm, start_index);

	if (path_amount > 1)
		ft_find_paths(farm, start_index, exit_index);
	printf("all paths found\n");
	exit(1);
	return ;
	(void)ant_amount;	//this will be needed later in moving ants through the found paths
}

/*	NOTES

	find an amount of paths equal to the amount of links to last or first room depending on which is smaller
	iterate through all rooms and mark visited rooms.
		mark all rooms as distance from starting room
		if dead end is found mark it as -3
		as rooms are iterated, paths to dead ends will be marked with -3 

	if a link has greater than current length
		use that link to calculate the new length of that path
		if length suddenly drops
			current path is not fastest way to move that way
		if length suddenly rises
			faster path through that room can be found
		if more paths have to be found to exit
			the path length numbers changing dont matter but shortest path should be used

*/
