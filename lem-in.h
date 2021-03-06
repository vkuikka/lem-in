/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:15:28 by vkuikka           #+#    #+#             */
/*   Updated: 2020/10/16 17:15:09 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <stdio.h> //remove this when project is done


/*
**	Room names are stored int **room_names so indexes can be used in calculations.
**	Ant numbers for each room are stored in *room_ants. Index is room index and value is ant number.
**	Total amount of ants is also stored in s_farm.
*/

// int			room_amount;	//total amount of rooms?
// int			ant_amount;		//total amount of ants

typedef struct		s_room
{
	char			*room_name;		//name of room that was given in input
	int				path_index;		//mark all found pahts so they can be used
	int				*links;			//array of links from this room
	int				link_amount;	//amount of links from this room
	int				signature;		//marks start and end. otherwise path finding lets following iterations know this room has been visited
}					t_room;

typedef struct		s_input
{
	char			*line;
	struct s_input	*next;
}					t_input;

typedef struct		s_links
{
	int				len;
	int				link;
	struct s_links	*next;
	struct s_links	*first;
}					t_links;

t_room		*ft_farm_alloc(t_room *farm, int *room_amount, int *ant_amount);
void		ft_ants(t_room *farm, int ant_amount, int room_amount);
int			*ft_add_num(int *arr, int num);

void		ft_find_paths(t_room *farm, int start_index, int end_index);

int			ft_find_room(t_room *farm, char *line, int room_amount);	//move to other file from farm_alloc.c

void		ft_error(char *message);
void		ft_print_room(t_room room);
void		ft_print_farm(t_room *farm);
void		ft_print_signatures(t_room *farm, int depth, int room);


#endif
