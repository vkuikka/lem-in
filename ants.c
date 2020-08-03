/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:23:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/03 21:34:40 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"


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

/*
**	signatures
**	0 not visited
**	distance from start
*/

void		ft_ants(t_room *farm, int ant_amount, int room_amount)
{
	t_links	*paths;
	int		exit_index;
	int		start_index;
	int		path;
	int		room;

	exit_index = ft_find_signature(farm, room_amount, -2);
	start_index = ft_find_signature(farm, room_amount, -1);
	paths = NULL;
	ft_new_list(&paths, 2);

	ft_add_link(&paths, 5);

	printf("%d %d\n", paths->first->link, paths->link);

	printf("%d links to end\n", farm[exit_index].link_amount);
	path = 0;


	paths->link = farm[start_index].links->link;

	/*
	paths = find max exit links amount of paths
	how?
		iterate through linked list and mark them
		when you reach a room that has no links start from beginning
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

	*/

	return ;
	ant_amount = 3;
}