/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:54:18 by vkuikka           #+#    #+#             */
/*   Updated: 2020/07/30 15:54:20 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "get_next_line.h"

#include <stdio.h>
#include "libft/includes/libft.h" 


int		*ft_add_room_index(int *arr, int num)
{
	int		*new;
	int		i;

	i = 0;
	while (arr[i] != -1)
		i++;
	if (!(new = (int *)malloc(sizeof(int) * i + 2)))
		ft_error("memory allocation failed");
	i = 0;
	while (arr[i] != -1)
	{
		new[i] = arr[i];
		i++;
	}
	arr[i] = num;
	new[i + 1] = -1;
	free(arr);
	return(new);
}

void	ft_handle_room_coord(t_room *farm, char **map, int line_amount)
{
	int		line_i;
	int		room;
	int		i;

	i = 0;
	line_i = 0;
	room = 0;
	while (line_i < line_amount)
	{
		i = 0;
		if (map[line_i][0] != '#')
			while (map[line_i][i] && map[line_i][i] != ' ')
				i++;
		if (i && map[line_i][i] == ' ')
			room++;
		line_i++;
	}						//room counting works

	if (!(farm = (t_room *)malloc(sizeof(t_room) * room)))
		ft_error("memory allocation failed\n");

	i = 0;
	while (i < room)
	{
		if (!(farm[i].links = (int *)malloc(sizeof(int) * 1)))
			ft_error("memory allocation failed\n");
		farm[i].links[0] = -1;
		i++;
	}
		
	room = 0;
	line_i = 0;
	while (line_i < line_amount)
	{
		i = 0;
		if (map[line_i][0] != '#')
			while (map[line_i][i] && map[line_i][i] != '-')
				i++;
		if (i && map[line_i][i] == '-')
		{
			farm[room].links = ft_add_room_index(farm[room].links, ft_atoi(&map[line_i][i + 1]));
			room++;
		}
		line_i++;
	}
	// for (int asd = 0; asd < room; asd++)
	// 	ft_putnbr_arr(&farm[asd].links, 1, 2);
	exit (1);
	
}

int		ft_rooms(char **map, t_room *farm, char **ant_names, int line_amount)
{
	int		room_amount;
	int		i;

	i = 0;
	room_amount = 0;
	ft_handle_room_coord(farm, map, line_amount);
	while (i < line_amount)
	{
		if (map[i][0] != '#')
			printf("asd");
		else if (!ft_strcmp(map[i], "##start"))
		{
			if (i == line_amount - 1)
				ft_error("invalid input\n");
		}
		else if (!ft_strcmp(map[i], "##end"))
		{
			ft_error("invalid input\n");
		}
		i++;
	}
	return (room_amount);
	farm = NULL;
	ant_names = NULL;
}

char	**ft_add_line_input(char **input, int array_len)
{
	char	**tmp;
	int		i;

	i = -1;
	if (!(tmp = (char **)malloc(sizeof(char *) * ++array_len + 1)))
		return (NULL);
	tmp[array_len] = NULL;
	while (++i < array_len)
		if (!(tmp[i] = ft_strdup(input[i])))
			ft_error("memory allocation failed\n");
	i = -1;
	while (++i < array_len)
		free(input[i]);
	free(input);
	return (tmp);
}

t_room		*ft_farm_alloc(t_room *farm, char **ant_names, int *room_amount, int *ant_amount)
{
	char	**map;
	int		line_amount;

	line_amount = -1;
	if (!(map = (char**)malloc(sizeof(char *) * 2)))
		ft_error("memory allocation failed\n");
	while (get_next_line(0, &map[++line_amount]))
		if (!(map = ft_add_line_input(map, line_amount)))
			return (NULL);
	*ant_amount = ft_atoi(map[0]);


	for (int j = 0; j < line_amount; j++)
		printf("%s\n", map[j]);
	//next get room amount and fill room struct values

	*room_amount = ft_rooms(map, farm, ant_names, line_amount);

	if (!(farm = (t_room *)malloc(sizeof(t_room) * *room_amount)))
		ft_error("memory allocation failed\n");


	farm[0].ant_index = ft_atoi(map[0]);
	for (int j = 1; j < *room_amount; j++)
		farm[j].ant_index = j + 1;

	for (int j = 0; j < *room_amount; j++)
		printf("%d\n", farm[j].ant_index);

	// while (1);

	return (farm);
	ant_names = NULL;
	ant_amount = NULL;
}
