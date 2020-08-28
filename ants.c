/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:23:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/28 15:50:50 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

//rm this
#include <stdio.h>

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
	printf("error: no exit");
	exit(1);
	return (-1);
}

static int	ft_dead_end(t_room *farm, int room, int exit_index, int distance)
{
	int		i;

	i = 0;
	while (i < farm[room].link_amount)
	{
		// printf("%d\n", i);
		// printf("%d\n", farm[room].link_amount);
		ft_print_room(farm[room]);
		farm[room].signature = distance;
		distance++;
		if (farm[room].signature == -3 || farm[room].link_amount < 2)
			return (0);
		else if (farm[farm[room].links[i]].signature == 0 && ft_dead_end(farm, farm[room].links[i], exit_index, distance))
			return(0);
		else if (room == exit_index || farm[farm[room].links[i]].signature == -2)
		{
			printf("end found from room %d\n", room);
			exit(1);
		}
		i++;
	}
	printf("%d reached end of loop\n", room);
	return (1);
}

static int	ft_map_farm(t_room *farm, int room, int **paths)
{
	int		i;
	int		valid_links;

	valid_links = 0;
	if (farm[room].link_amount < 2 && farm[room].signature != -1)
	{
		farm[room].signature = -3;
		return (0);
	}
	i = -1;
	ft_print_room(farm[room]);
	while (++i < farm[room].link_amount && farm[room].links[i] != -1)
		if (farm[farm[room].links[i]].signature == -2)
		{
			ft_print_room(farm[farm[room].links[i]]);
			exit(1);
		}
	i = 0;
	while (i < farm[room].link_amount && farm[room].links[i] != -1)
	{
		if (farm[farm[room].links[i]].signature == 0)
			if (ft_map_farm(farm, farm[room].links[i], NULL))
				valid_links++;
		i++;
	}
	if (valid_links < 2)
	{
		farm[room].signature = -3;
		return (0);
	}
	// printf("%d\n", room);
	farm[room].signature = 99999;
	return (1);

	farm = NULL;
	paths = NULL;
}

/*
**	signatures
**
**	-3 dead end
**	-2 end
**	-1 start
**	0 not visited
**	0 < distance from start
**
*/

void		ft_ants(t_room *farm, int ant_amount, int room_amount)
{
	int		**paths;
	int		start_index;
	int		exit_index;
	int		distance;
	int		room;
	int		path;
	int		i;

	exit_index = ft_find_signature(farm, room_amount, -2);
	start_index = ft_find_signature(farm, room_amount, -1);
	if (!(paths = (int **)malloc(sizeof(int *) * farm[exit_index].link_amount + 1)))
		ft_error("memory allocation failed");
	room = 0;
	while (room < farm[exit_index].link_amount + 1)
	{
		if (!(paths[room] = (int *)malloc(sizeof(int) * 1)))
			ft_error("memory allocation failed");
		paths[room][0] = -1;
		room++;
	}

	path = 0;

	printf("end links: ");
	for (int asd = 0; asd < farm[exit_index].link_amount; asd++)
		printf("%d ", farm[exit_index].links[asd]);
	printf("\n");

	printf("start links: ");
	for (int asd = 0; asd < farm[start_index].link_amount; asd++)
		printf("%d ", farm[start_index].links[asd]);
	printf("\n\n");

	ft_map_farm(farm, start_index, paths);

	exit(1);

	ft_dead_end(farm, start_index, exit_index, 1);
	printf("no end apparently\n");
	exit(1);


	// if (farm[farm[room].links[path]].link_amount == 1)
	// 	farm[farm[room].links[path]].signature = -3;

	// printf("printing paths:\n");
	// for (int a = 0; a < farm[exit_index].link_amount + 1; a++)
	// {
	// 	for (int s = 0; paths[a][s] != -1; s++)
	// 		printf("%d", paths[a][s]);
	// 	printf("\n");
	// }

	// paths[0] = ft_add_num(paths[0], room);
	distance = 0;

	i = 0;
	room = start_index;
	// while ()
	{
		while (room != exit_index)
		{
			room = farm[room].links[path];
		}
		i++;
	}


	/*
	find exit room links amount of paths
	how?
		iterate through linked list and mark them
		when you reach a room that has no links mark it as -3 and start from beginning
		mark rooms by amount of links visited
		always look at the next rooms signature and amount of links
		if amount of links is greater than signature
			move to that room
		else
			use unused link from this room
		{
			keep counting the length of the path
			if a link has a greater length than current length
				use that link to calculate the new length of that path
				if length suddenly drops
					current path is not fastest way to move that way
				if length suddenly rises
					faster path through that room can be found
				if more paths have to be found to exit
					the path length numbers changing dont matter but shortest path should be used
		} or {
			try iterating to points that definitely lead to end
			if ant cannot go to one of those without going through the other
				another path has to be found there
		}

	find out what amount of ants can be sent to each path by calculating their lengths
	(data structure may have to be modified linked list is hard or maybe add different linked list with lengths)

	while ants in start
	{
		move ants through path
		if less than longest path length ants are in start (paths are in length order to speed up this)
			stop using that path
	}

	if you cant find a path to exit with the amount of wanted paths, try without using one of earlier found paths.
	if that results in a shorter path than earlier or if that results in more paths to exit then use the new one.

	*/

	return ;
	ant_amount = 3;
	room = 3;
}