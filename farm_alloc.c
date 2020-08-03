/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:54:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/03 20:23:15 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "get_next_line.h"

#include <stdio.h>
#include "libft/includes/libft.h" 

int		ft_find_room(t_room *farm, char *line, int room_amount)
{
	int		i;
	int		changed_i;
	char	c;

	c = '\0';
	changed_i = 0;
	while (line[changed_i] && line[changed_i] != '-' && line[changed_i] != ' ')
	{
		changed_i++;
		if (line[changed_i] == '-')
			c = '-';
		else if (line[changed_i] == ' ')
			c = ' ';
	}
	line[changed_i] = '\0';
	i = -1;
	while (++i < room_amount)
		if (!ft_strcmp(line, farm[i].room_name))
		{
			line[changed_i] = c;
			return (i);
		}
	printf("Formatting error: no matching room found for link %s\n", line);
	exit(1);
	return (i);
}

void	ft_room_names(t_room *farm, t_input *input)
{
	int		room_i;
	int		i;

	i = 0;
	room_i = 0;
	input = input->next;
	while (input->next)
	{
		if (input->line[0] != '#' && !(ft_strstr(input->line, "-")))
		{
			i = 0;
			while (input->line[i] != ' ')
				i++;
			if (!(farm[room_i].room_name = (char *)malloc(sizeof(char) * i + 1)))
				ft_error("memory allocation failed");
			i = -1;
			while (input->line[++i] != ' ')
				farm[room_i].room_name[i] = input->line[i];
			farm[room_i].room_name[i] = '\0';
			room_i++;
		}
		else if (input->line[0] != '#')
			return ;
		input = input->next;
	}
}

t_room		*ft_handle_rooms(int *room_amount, t_input *input)
{
	t_input	*start;
	t_room	*farm;
	int		room;
	int		i;

	i = 0;
	start = input;
	*room_amount = 0;
	while (input->next)
	{
		if (input->line[0] != '#' && !(i = 0))
			while (input->line[i] && input->line[i] != ' ')
				i++;
		if (i && input->line[i] == ' ')
			*room_amount += 1;
		input = input->next;
	}
	printf("%d rooms\n", *room_amount);
	if (!(farm = (t_room *)malloc(sizeof(t_room) * *room_amount)))
		ft_error("memory allocation failed\n");
	ft_room_names(farm, start);

	i = 0;
	while (i < *room_amount)
	{
		if (!(farm[i].links = (t_links *)malloc(sizeof(t_links))))
			ft_error("memory allocation failed\n");
		farm[i].links->link = 0;
		farm[i].links->next = NULL;
		farm[i].links->first = farm[i].links;
		farm[i].link_amount = 0;
		farm[i].ant_index = -1;
		i++;
	}
	room = 0;
	input = start;

	while (input->next)
	{
		i = 0;
		if (input->line[0] != '#')
			while (input->line[i] && input->line[i] != '-')
				i++;
		if (i && input->line[i] == '-')
		{
			room = ft_find_room(farm, input->line, *room_amount);
			farm[room].links->link = ft_find_room(farm, &input->line[i + 1], *room_amount);
			if (!(farm[room].links->next = (t_links *)malloc(sizeof(t_links))))
				ft_error("memory allocation failed\n");
			farm[room].links->next->first = farm[room].links->first;
			farm[room].links->next->next = NULL;
			farm[room].links = farm[room].links->next;
			farm[room].link_amount++;
		}
		input = input->next;
	}
	return (farm);
}

int		ft_rooms(t_input *input, t_room **farm, int line_amount)
{
	int		last_instruction;
	int		room_amount;
	int		i;

	i = 0;
	room_amount = 0;
	last_instruction = 0;
	*farm = ft_handle_rooms(&room_amount, input);
	while (i < line_amount - 1 && last_instruction < 2)
	{
		if (!ft_strcmp(input->line, "##start") && input->next)
		{
			farm[0][ft_find_room(*farm, input->next->line, room_amount)].signature = -1;
			last_instruction++;
		}
		else if (!ft_strcmp(input->line, "##end") && input->next)
		{
			farm[0][ft_find_room(*farm, input->next->line, room_amount)].signature = -2;
			last_instruction++;
		}
		free(input->line);
		input = input->next;
		i++;
	}
	return (room_amount);
}

t_room		*ft_farm_alloc(t_room *farm, int *room_amount, int *ant_amount)
{
	t_input	*input;
	t_input	*tmp;
	int		line_amount;
	int		gnl_error;
	int		i;

	i = 0;
	line_amount = -1;
	if (!(input = (t_input *)malloc(sizeof(t_input) * 1)))
		ft_error("memory allocation failed\n");
	tmp = input;
	input->line = NULL;
	while (0 < (gnl_error = get_next_line(0, &input->line)))
	{
		line_amount++;
		if (!(input->next = (t_input *)malloc(sizeof(t_input) * 1)))
			ft_error("memory allocation failed\n");
		input = input->next;
	}
	if (gnl_error < 0)
		ft_error("could not read and save file\n");
	if (!(input->next = (t_input *)malloc(sizeof(t_input) * 1)))
		ft_error("memory allocation failed\n");
	input = input->next;
	input->line = NULL;
	input->next = NULL;
	*ant_amount = ft_atoi(tmp->line);
	*room_amount = ft_rooms(tmp, &farm, line_amount);
	input = tmp;
	return (farm);
}
	// for (int a = 0; a < room_amount; a++)
	// 	ft_print_room(farm[0][a]);