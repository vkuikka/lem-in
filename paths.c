/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:47:06 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/28 13:02:09 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		ft_path_trace(t_room *farm, int trace_start, int path);

static void	ft_clean_path(t_room *farm, int link)
{
	int		tmp;
	int		i;

	i = 0;
	tmp = link;
	// printf("clean path from:\n");
	// ft_print_room(farm[link]);
	while (farm[tmp].path_index != -1)
	{
		i = 0;
		while (i < farm[tmp].link_amount)
		{
			if (farm[farm[tmp].links[i]].path_index == -1)
			{
				tmp = farm[tmp].links[i];
				break ;
			}
			if (farm[farm[tmp].links[i]].path_index == farm[link].path_index &&
				farm[farm[tmp].links[i]].signature < farm[tmp].signature)
			{
				tmp = farm[tmp].links[i];
				farm[tmp].path_index = 0;
				i = 0;
			}
			else if (i == farm[tmp].link_amount - 1)
				ft_error("couldnt clean path because next link was not found. FIX!!!\n");
			else
				i++;
		}
	}
}

static int	ft_solve_intersection(t_room *farm, int room, int link, int path)
{
	int		previous;
	int		best_link;
	int		best_dist;
	int		tmp;
	int		i;

	// printf("intersection between:\n");
	// ft_print_room(farm[room]);
	// ft_print_room(farm[link]);

	i = 0;
	tmp = link;
	previous = link;
	best_link = -1;
	best_dist = 0;
	while (farm[tmp].path_index != -2)
	{
		if (i < farm[tmp].link_amount &&
			farm[tmp].links[i] != previous &&
			farm[farm[tmp].links[i]].path_index == path &&
			farm[farm[tmp].links[i]].signature > farm[tmp].signature)
		{
			printf("%d %d %d\n", tmp, previous, i);
			previous = tmp;
			tmp = farm[tmp].links[i];
			best_dist++;
			i = 0;
			while (i < farm[tmp].link_amount)
			{
				// printf("%d %d %d\n", best_link, i, best_dist);
				if ((best_link == -1 || farm[farm[tmp].links[i]].signature < best_dist) &&
					farm[tmp].links[i] != previous &&
					farm[farm[tmp].links[i]].path_index != -2 &&
					farm[farm[tmp].links[i]].path_index != farm[tmp].path_index)
				{
					best_link = farm[tmp].links[i];
					printf("backtrack secondary found %s\n", farm[best_link].room_name);
					best_dist = farm[best_link].signature;
				}
				i++;
			}
			i = 0;
		}
		else if (i >= farm[tmp].link_amount ||
				farm[farm[tmp].links[i]].path_index == -2)
			break ;
		else
			i++;
	}
	if (best_link == -1)
		ft_error("no secondary path for intercepted path was found??? FIX\n");
	i = 0;
	while (i < farm[best_link].link_amount)
	{
		if (farm[farm[best_link].links[i]].path_index == farm[link].path_index)
		{
			ft_clean_path(farm, farm[best_link].links[i]);
			break;
		}
		i++;
	}

	ft_path_trace(farm, room, farm[room].path_index);
	farm[best_link].path_index = farm[tmp].path_index;
	ft_path_trace(farm, best_link, farm[best_link].path_index);

	return (0);
}

static int	ft_next_link(t_room *farm, int path, int room)
{
	int				best_link;
	int				best_len;
	int				i;

	i = 0;
	best_len = -1;
	best_link = -1;
	while (i < farm[room].link_amount)
	{
		while (farm[farm[room].links[i]].signature == -1)	//this skips unusable links
			i++;
		if (i >= farm[room].link_amount)
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
		printf("intercepting from room: %s\n", farm[room].room_name);
		ft_print_room(farm[room]);


		// if no possible link is found trace both paths backwards until the shortest path between them is found.
		// if during this more paths are found trace all paths (recursion?) until shortest paths are found
		i = 0;
		while (i < farm[room].link_amount)
		{
			if (farm[farm[room].links[i]].signature < best_len || best_len == -1)
			{
				best_link = farm[room].links[i];
				best_len = farm[farm[room].links[i]].signature;
			}
			i++;
		}
		// printf("best link: %d\n", best_link);
		if (farm[best_link].path_index == 0)	//error checking
			ft_error("false intersection fix this!!!!!!!\n");
		ft_solve_intersection(farm, room, best_link, farm[best_link].path_index);
		printf("intersection solved\n");
		exit(1);
		return (-1);
	}
	// printf("path %d\n", path);
	// ft_print_room(farm[best_link]);
	if (farm[best_link].path_index != -1)
		farm[best_link].path_index = path;
	return (best_link);
}

void		ft_path_trace(t_room *farm, int trace_start, int path)
{
	int room;

	room = trace_start;
	while (farm[room].path_index != -1)
		room = ft_next_link(farm, path, room);
	// printf("path found to end/start----------------------------------------\n");
	// ft_print_farm(farm);
}

void		ft_find_paths(t_room *farm, int start_index, int end_index)
{
	int		path_amount;
	int		found_paths;
	int		i;

	i = 0;
	path_amount = 0;
	while (i < farm[start_index].link_amount)
		if (farm[farm[start_index].links[i++]].signature != -1)
			path_amount++;
	path_amount = path_amount < farm[end_index].link_amount ?
				path_amount : farm[end_index].link_amount;
	found_paths = 1;
	while (found_paths <= path_amount)
	{
		ft_path_trace(farm, end_index, found_paths);
		found_paths++;
	}
}
