/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:15:28 by vkuikka           #+#    #+#             */
/*   Updated: 2020/07/30 17:16:40 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEMIN_H
# define LEMIN_H
# include "libft.h"

/*
**	Room names are stored int **room_names so indexes can be used in calculations.
**	Ant numbers for each room are stored in *room_ants. Index is room index and value is ant number.
**	Total amount of ants is also stored in s_farm.
*/

// int			room_amount;	//total amount of rooms?
// int			ant_amount;		//total amount of ants

typedef struct	s_room
{
	int			ant_index;		//ant index
	int			*links;			//links from this room
	char		*room_name;		//name of room that was given in input
}				t_room;

t_room		*ft_farm_alloc(t_room *farm, char **ant_names, int *room_amount, int *ant_amount);
void		ft_error(char *message);

#endif