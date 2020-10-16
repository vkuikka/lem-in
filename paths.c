/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:47:06 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/16 17:15:14 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	ft_solve_intersection(t_room *farm, int room, int path, int link)
{
	int		previous;
	int		tmp;
	int		i;

	i = 0;
	ft_print_room(farm[link]);
	ft_print_room(farm[room]);

	tmp = link;
	previous = tmp;
	while (farm[tmp].signature != -2)
	{
		if (farm[tmp].links[i] != previous &&
			(farm[farm[tmp].links[i]].path_index == farm[link].path_index ||
			farm[farm[tmp].links[i]].signature == -2))
		{
			previous = tmp;
			tmp = farm[tmp].links[i];
			i = 0;
		}
		else
			i++;
	}
	ft_print_room(farm[tmp]);
	printf("intercept not solved\n");
	exit(1);
	return (0);
	farm = NULL;
	room = 0;
	path = 0;
	link = 0;
}

static int	ft_next_link(t_room *farm, int path, int room, int path_amount)
{
	static t_room	**secondary = NULL;
	static int		secondary_range = 0;
	int				best_link;
	int				best_len;
	int				i;

	best_len = -1;
	best_link = -1;
	if (!secondary)
	{
		i = -1;
		secondary_range = 0;
		if (!(secondary = (t_room **)malloc(sizeof(t_room *) * path_amount)))
			ft_error("could not allocate memory\n");
		while (++i < path_amount)
			secondary[i] = NULL;
	}
	i = 0;
	ft_print_room(farm[room]);
	while (i < farm[room].link_amount)
	{
		while (farm[farm[room].links[i]].signature < 0)
		{
			if (farm[farm[room].links[i]].signature == -1)
				return (farm[room].links[i]);
			i++;
		}
		if (i >= farm[room].link_amount)
			break;

		// direction of secondary link should be checked u-turns are not made

		if ((farm[farm[room].links[i]].signature < best_len || best_len == -1))	//FIX CONTENTS OF THIS CONDITION
		{
			if (farm[farm[room].links[i]].path_index == -1)
			{
				if (farm[farm[room].links[i]].path_index != path && farm[room].signature != -2 &&
					best_len != -1 && (secondary[path] == NULL || secondary[path]->signature >=
					farm[farm[room].links[i]].signature + secondary_range))
				{
					printf("%d %d %d\n", path, farm[best_link].path_index, best_link);
					secondary_range = 0;
					secondary[path] = &farm[best_link];
					printf("secondary saved %s\n", farm[best_link].room_name);
				}
				best_len = farm[farm[room].links[i]].signature;
				best_link = farm[room].links[i];
			}
		}
		else if (farm[farm[room].links[i]].path_index != path && farm[room].signature != -2 &&
			(secondary[path] == NULL || secondary[path]->signature >=
			farm[farm[room].links[i]].signature + secondary_range))
		{
			printf("%d %d %d\n", path, farm[farm[room].links[i]].path_index, room);
			secondary_range = 0;
			secondary[path] = &farm[farm[room].links[i]];
			printf("secondary saved %d\n", farm[room].links[i]);
		}
		i++;
	}
	printf("\n");
	/*
		if no possible link is found trace both paths backwards until the shortest path between them is found.
		if during this more paths are found trace all paths (recursion?) until shortest paths are found
	*/
	if (best_len == -1)
	{
		if (secondary[path])
		{
			printf("\n%d\n\n", secondary_range);
			ft_print_room(*secondary[path]);
		}
		else
			printf("no secondary!\n");

		// printf("%d\n", room);
		// ft_print_room(farm[best_link]);
		printf("current room name: %s\n", farm[room].room_name);
		i = 0;
		while (i < farm[room].link_amount)
		{
			if (farm[farm[room].links[i]].signature > 0 &&
				(best_link == -1 || farm[farm[room].links[i]].signature < farm[best_link].signature))
				best_link = farm[room].links[i];
			i++;
		}

		ft_solve_intersection(farm, room, path, best_link);
		printf("exit because path intercepts another\n");
		exit(1);
		return (-1);
	}
	secondary_range++;
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
	printf("possible paths: %d\n\n", path_amount);

	found_paths = 0;
	while (found_paths < path_amount)
	{
		room = end_index;
		printf("%d\n", room);
		while (room != start_index)
			room = ft_next_link(farm, found_paths, room, path_amount);
		printf("path found to end/start\n");
		found_paths++;
	}
}
