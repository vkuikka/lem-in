/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:15:28 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/03 20:26:16 by vkuikka          ###   ########.fr       */
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

typedef struct		s_room
{
	char			*room_name;		//name of room that was given in input
	int				ant_index;		//ant index (if room has an ant)
	struct s_links	*links;			//list of links from this room
	int				link_amount;
	int				signature;		//marks start and end. otherwise path finding lets following iterations know this room has been visited
}					t_room;

typedef struct		s_input
{
	char			*line;
	struct s_input	*next;
}					t_input;

typedef struct		s_links
{
	int				link;
	struct s_links	*next;
	struct s_links	*first;
}					t_links;



t_room		*ft_farm_alloc(t_room *farm, int *room_amount, int *ant_amount);
void		ft_ants(t_room *farm, int ant_amount, int room_amount);
void		ft_add_link(t_links **list, int link_index);
void		ft_new_list(t_links **link, int link_value);

int			ft_find_room(t_room *farm, char *line, int room_amount);	//move to other file from farm_alloc.c

void		ft_error(char *message);
void		ft_print_room(t_room room);


#endif
