/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:23:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/31 16:06:16 by vkuikka          ###   ########.fr       */
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
		// ft_print_room(farm[room]);
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
	// while (++i < farm[room].link_amount && farm[room].links[i] != -1)
	// {
	// 	if (farm[farm[room].links[i]].signature == -2)
	// 	{
	// 		ft_print_farm(farm);
	// 		printf("\nend: \n");
	// 		ft_print_room(farm[farm[room].links[i]]);
	// 		for (int i = 0; farm[i].signature != -2;)
	// 		{
	// 			printf("%s ", farm[i].room_name);
	// 			printf("%d\n", farm[i].signature);
	// 			for (int j = 0; j < farm[i].link_amount; j++)
	// 			{
	// 				if (farm[i].signature == -1)
	// 					farm[i].signature = 0;
	// 				if (farm[farm[i].links[j]].signature == farm[i].signature + 1)
	// 				{
	// 					for (int k = 0; k < farm[i].link_amount; k++)
	// 						if (farm[farm[i].links[k]].signature == farm[i].signature + 1 && j != k)
	// 						{
	// 							printf("multiple possible paths!!!!!!\n");
	// 							exit(1);
	// 						}
	// 					i = farm[i].links[j];
	// 					break;
	// 				}
	// 				if (farm[farm[i].links[j]].signature == -2)
	// 				{
	// 					printf("%s ", farm[farm[i].links[j]].room_name);
	// 					printf("%d\n", farm[farm[i].links[j]].signature);
	// 					exit(1);
	// 				}
	// 			}
	// 		}
	// 		exit(1);
	// 	}
	// }
	i = 0;
	while (i < farm[room].link_amount && farm[room].links[i] != -1)
	{
		if (farm[farm[room].links[i]].signature == -2)
		{
			return (1);
		}
		if (farm[farm[room].links[i]].signature == 0 ||
			farm[farm[room].links[i]].signature > farm[room].signature + 1)
		{
			farm[farm[room].links[i]].signature = farm[room].signature + 1;
			if (farm[room].signature == -1)
				farm[farm[room].links[i]].signature = 1;

			paths[0][0] = room;
			paths[0]++;
			if (ft_map_farm(farm, farm[room].links[i], paths))
				valid_links++;
		}
		i++;
	}
	// printf("%d\n", room);
	if (valid_links < 1)
	{
		// if (farm[room].signature == -2 ||
		// 	farm[room].signature == -1)
		// 	return (0);
		farm[room].signature = -3;
		return (0);
	}

	// farm[room].signature = ;
	// printf("reached end\n");
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
	int		room;

	exit_index = ft_find_signature(farm, room_amount, -2);
	start_index = ft_find_signature(farm, room_amount, -1);
	if (!(paths = (int **)malloc(sizeof(int *) * farm[exit_index].link_amount + 1)))
		ft_error("memory allocation failed");
	room = 0;
	while (room < farm[exit_index].link_amount + 1)
	{
		if (!(paths[room] = (int *)malloc(sizeof(int) * room_amount)))
			ft_error("memory allocation failed");
		ft_memset(paths[room], -1, room_amount * 4);
		room++;
	}


	printf("end links: ");
	for (int asd = 0; asd < farm[exit_index].link_amount; asd++)
		printf("%d ", farm[exit_index].links[asd]);
	printf("\n");

	printf("start links: ");
	for (int asd = 0; asd < farm[start_index].link_amount; asd++)
		printf("%d ", farm[start_index].links[asd]);
	printf("\n\n");

	ft_map_farm(farm, start_index, paths + 1);

	ft_print_farm(farm);
	// exit(1);
	printf("\nfind: \n");
	ft_print_room(farm[0]);
	int last = -123;
	for (int i = exit_index; farm[i].signature != -1;)
	{
		printf("%s ", farm[i].room_name);
		printf("%d\n", farm[i].signature);
		if (i == last || farm[i].signature == -3)
			exit(1);
		last = i;

		int	smallest;
		smallest = -123;
		for (int j = 0; j < farm[i].link_amount; j++)
			if (farm[farm[i].links[j]].signature > 0)
				smallest = farm[i].links[j];
		if (smallest == -123)
		{
			printf("\n\nno valid path from:\n");
			ft_print_room(farm[i]);
			if (farm[i].link_amount)
				ft_print_room(farm[farm[i].links[0]]);
			exit(1);
		}
		for (int j = 0; j < farm[i].link_amount; j++)
		{
			if (farm[farm[i].links[j]].signature <= farm[smallest].signature && farm[farm[i].links[j]].signature > 0)
			{
				// for (int k = 0; k < farm[i].link_amount; k++)
				// 	if (farm[farm[i].links[k]].signature == farm[i].signature + 1 && j != k)
				// 	{
				// 		printf("multiple possible paths!!!!!!\n");
				// 		// exit(1);
				// 	}
				farm[i].signature = -3;
				i = farm[i].links[j];
				break;
			}
			if (farm[farm[i].links[j]].signature == -1)
			{
				printf("%s ", farm[farm[i].links[j]].room_name);
				printf("%d\n", farm[farm[i].links[j]].signature);
				exit(1);
			}
		}
		if (farm[i].signature == -1)
		{
			printf("%s ", farm[i].room_name);
			printf("%d\n", farm[i].signature);
		}
	}

	exit(1);

	ft_dead_end(farm, start_index, exit_index, 1);
	printf("no end apparently\n");
	exit(1);


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