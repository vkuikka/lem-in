/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:23:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/16 13:49:02 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h> //remove this when project is done

static int	ft_find_signature(t_room *farm, int room_amount, int signature)
{
	int		i;

	i = 0;
	while (i < room_amount)
	{
		if (farm[i].signature == signature)
			return (i);
		i++;
	}
	printf("error: room not found fix me now\n");
	exit(1);
	return (-1);
}

static int	ft_map_farm(t_room *farm, int room)
{
	int		i;
	int		valid_links;

	valid_links = 0;
	if (farm[room].link_amount < 2 && farm[room].signature != -1)
	{
		farm[room].signature = -3;
		return (0);
	}
	i = 0;
	while (i < farm[room].link_amount && farm[room].links[i] != -1)
	{
		if (farm[farm[room].links[i]].signature == -2)
			return (1);
		if (farm[farm[room].links[i]].signature == 0 ||
			farm[farm[room].links[i]].signature > farm[room].signature + 1)
		{
			farm[farm[room].links[i]].signature = farm[room].signature + 1;
			if (farm[room].signature == -1)
				farm[farm[room].links[i]].signature = 1;

			if (ft_map_farm(farm, farm[room].links[i]))
				valid_links++;
		}
		i++;
	}
	if (valid_links < 1)
	{
		// if (farm[room].signature == -2 ||
		// 	farm[room].signature == -1)
		// 	return (0);
		farm[room].signature = -3;
		return (0);
	}
	return (1);
}

static int	ft_next_link(t_room *farm, int path, int room)
{
	static t_room	*secondary = NULL;
	static int		secondary_range = 0;
	int				best_link;
	int				best_len;
	int				i;

	i = 0;
	best_len = -1;
	best_link = -1;
	if (secondary && secondary->path_index != path)
	{
		secondary_range = 0;
		secondary = NULL;
	}
	while (i < farm[room].link_amount)
	{
		if (farm[farm[room].links[i]].signature == -1)
			return (farm[room].links[i]);
		if (farm[farm[room].links[i]].signature > -1 &&
			(farm[farm[room].links[i]].signature < best_len || best_len == -1))
		{
			if (farm[farm[room].links[i]].path_index != -1 && 
				farm[farm[room].links[i]].path_index != path &&
				(secondary == NULL || secondary->signature >
				farm[farm[room].links[i]].signature + secondary_range))
			{
				secondary_range = 0;
				secondary = &farm[farm[room].links[i]];
			}
			else if (farm[farm[room].links[i]].path_index == -1)
			{
				best_len = farm[farm[room].links[i]].signature;
				best_link = farm[room].links[i];
			}
		}
		i++;
	}
	secondary_range++;
	/*
		if no possible link is found trace both paths backwards until the shortest path between them is found.
		if during this more paths are found trace all paths (recursion?) until shortest paths are found
	*/
	if (best_len == -1)
	{
		// ft_secondary_path(); //?
		printf("\n%d\n\n", secondary_range);
		ft_print_room(*secondary);
		printf("exit because path intercepts another\n");
		exit(1);
	}

	farm[best_link].path_index = path;
	return (best_link);
}

void		ft_find_paths(t_room *farm, int start_index, int end_index)
{
	int		path_amount;
	int		found_paths;
	int		room;
	int		i;

	i = 0;
	path_amount = 0;
	while (i < farm[start_index].link_amount)
		if (farm[farm[start_index].links[i++]].signature != -3)
			path_amount++;
	path_amount = path_amount < farm[end_index].link_amount ?
				path_amount : farm[end_index].link_amount;
	printf("possible paths: %d\n", path_amount);

	found_paths = 0;
	while (found_paths < path_amount)
	{
		room = end_index;
		while (room != start_index)
			room = ft_next_link(farm, found_paths, room);
		printf("path found to end/start\n");
		found_paths++;
	}
}

/*
**	signatures
**
**	-3 dead end
**	-2 end
**	-1 start
**	0 not visited
**	0 < distance from start
*/

void		ft_ants(t_room *farm, int ant_amount, int room_amount)
{
	// int		**paths;
	int		path_amount;
	int		start_index;
	int		exit_index;
	int		room;

	exit_index = ft_find_signature(farm, room_amount, -2);
	start_index = ft_find_signature(farm, room_amount, -1);
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


	ft_map_farm(farm, start_index);
	//if there is only one link in either start or exit stop here
	ft_find_paths(farm, start_index, exit_index);
	exit(1);

	ft_print_farm(farm);

	printf("\nfind: \n\n");
	// ft_print_room(farm[0]);
	exit(1);




	return ;
	ant_amount = 3;
	room = 3;
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
