/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:47:06 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/26 15:34:49 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	ft_solve_intersection(t_room *farm, int room, int path, int link)
{
	int		previous;
	int		best_link;
	int		best_dist;
	int		tmp;
	int		i;

	i = 0;
	// ft_print_room(farm[link]);
	// ft_print_room(farm[room]);
	tmp = link;
	previous = tmp;
	best_link = -1;
	best_dist = 0;
	while (farm[tmp].signature != -2)
	{
		if (farm[tmp].links[i] != previous &&
			(farm[farm[tmp].links[i]].path_index == farm[link].path_index ||
			farm[farm[tmp].links[i]].signature == -2))
		{
			previous = tmp;
			tmp = farm[tmp].links[i];
			best_dist++;
			i = 0;
			while (i < farm[tmp].link_amount && farm[tmp].signature != -2)
			{
				if ((best_link == -1 || farm[farm[tmp].links[i]].signature < farm[best_link].signature - best_dist) &&
					farm[farm[tmp].links[i]].signature != -2 &&
					farm[farm[tmp].links[i]].path_index != path &&
					farm[farm[tmp].links[i]].path_index != farm[tmp].path_index)
				{
					best_link = farm[tmp].links[i];
					printf("backtrack secondary found %s\n", farm[best_link].room_name);
					best_dist = 0;
				}
				i++;
			}
			i = 0;
		}
		else
			i++;
	}
	if (best_link != -1)
	{
		i = 0;
		while (i < farm[best_link].link_amount)
			i++;
	}
	else
		ft_error("no secondary path for intercepted path was found???\n");
	ft_print_room(farm[best_link]);
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
	int				best_link;
	int				best_len;
	int				i;

	best_len = -1;
	best_link = -1;
	printf("%d\n", room);
	i = 0;
	while (i < farm[room].link_amount)
	{
		while (farm[farm[room].links[i]].signature == -1)	//this skips unusable links
			if (i++ >= farm[room].link_amount)
				break;
		if ((farm[farm[room].links[i]].signature < best_len || best_len == -1) &&
			(farm[farm[room].links[i]].path_index == 0 ||
			farm[farm[room].links[i]].path_index == -1))
			{
				best_len = farm[farm[room].links[i]].signature;
				best_link = farm[room].links[i];
			}
		i++;
	}
	if (best_len == -1)
	{
		printf("intercepting room: %s\n", farm[room].room_name);
		printF("path: %d\n", path);

		// if no possible link is found trace both paths backwards until the shortest path between them is found.
		// if during this more paths are found trace all paths (recursion?) until shortest paths are found
		ft_solve_intersection(farm, room, path, best_link);
		printf("intercept solved\n");
		exit(1);
		return (-1);
	}
	farm[best_link].path_index = path;
	return (best_link);
	(void)path_amount;
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

	found_paths = 1;
	while (found_paths <= path_amount)
	{
		room = end_index;
		while (room != start_index)
			room = ft_next_link(farm, found_paths, room, path_amount);
		printf("path found to end/start\n");
		found_paths++;
	}
}
