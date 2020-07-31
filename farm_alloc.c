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

int		ft_current_room(int room_amount, int line_i, char **map, t_room *farm)
{
	int		i;

	i = 0;
	while (i < room_amount)
	{
		if (ft_strstr(map[line_i], farm[i].room_name) == map[line_i])
			break;
		i++;
	}
	return (i);
}

int		ft_find_name(t_room *farm, char *name, int room_amount)
{
	int		i;

	i = 0;
	while (i < room_amount)
	{
		if (!ft_strcmp(farm[i].room_name, name))
			return (i);
		i++;
	}
	printf("ft_find_name error if this happens edit\n");
	exit(1);
	return (-1);
}

void	ft_room_names(t_room *farm, char **map, int line_amount)
{
	int		line_i;
	int		room_i;
	int		i;

	i = 0;
	room_i = 0;
	line_i = -1;
	map++;
	while (++line_i < line_amount)
		if (map[line_i][0] != '#' && !(ft_strstr(map[line_i], "-")))
		{
			i = 0;
			while (map[line_i][i] != ' ')
				i++;
			if (!(farm[room_i].room_name = (char *)malloc(sizeof(char) * i + 1)))
				ft_error("memory allocation failed");
			i = -1;
			while (map[line_i][++i] != ' ')
				farm[room_i].room_name[i] = map[line_i][i];
			farm[room_i].room_name[i] = '\0';
			room_i++;
		}
		else if (map[line_i][0] != '#')
			return ;
}

int		*ft_add_room_index(int *arr, int num)
{
	int		*new;
	int		len;
	int		i;

	len = 0;
	while (arr[len] != -1)
		len++;
	len++;
	if (!(new = (int *)malloc(sizeof(int) * (len + 1))))
		ft_error("memory allocation failed");
	new[len] = -1;
	i = 0;
	while (i < len)
	{
		new[i] = arr[i];
		i++;
	}
	new[i - 1] = num;
	free(arr);
	return(new);
}

t_room		*ft_handle_rooms(int *room_amount, char **map, int line_amount)
{
	// int		room_amount;
	t_room	*farm;
	int		line_i;
	int		room;
	int		i;

	i = 0;
	line_i = 0;
	*room_amount = 0;
	while (line_i < line_amount)
	{
		i = 0;
		if (map[line_i][0] != '#')
			while (map[line_i][i] && map[line_i][i] != ' ')
				i++;
		if (i && map[line_i][i] == ' ')
			*room_amount += 1;
		line_i++;
	}						//room counting works
	if (!(farm = (t_room *)malloc(sizeof(t_room) * *room_amount)))
		ft_error("memory allocation failed\n");
	ft_room_names(farm, map, line_amount);

	i = 0;
	while (i < *room_amount)
	{
		if (!(farm[i].links = (int *)malloc(sizeof(int) * 1)))
			ft_error("memory allocation failed\n");
		farm[i].links[0] = -1;
		farm[i].link_amount = 0;
		farm[i].ant_index = -1;
		i++;
	}
	printf("\n~~~~~~\n\n");

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
			room = ft_current_room(*room_amount, line_i, map, farm);
			farm[room].links = ft_add_room_index(farm[room].links, ft_find_name(farm, &map[line_i][i + 1], *room_amount));
			farm[room].link_amount++;
		}
		line_i++;
	}

	for (int asd = 0; asd < *room_amount; asd++)
	{
		printf("%d: ", asd);
		for (int zxc = 0; zxc < farm[asd].link_amount; zxc++)
			printf("%d ", farm[asd].links[zxc]);
		printf("\n");
	}
	return (farm);
}

int		ft_rooms(char **map, t_room *farm, char **ant_nums, int line_amount)
{
	int		room_amount;
	int		i;

	i = 0;
	room_amount = 0;
	farm = ft_handle_rooms(&room_amount, map, line_amount);
	while (i < line_amount)
	{
		if (!ft_strcmp(map[i], "##start"))
			farm[i].signature = -1;
		else if (!ft_strcmp(map[i], "##end"))
			farm[i].signature = -2;
		else
			farm[i].signature = 0;
		i++;
	}
	return (room_amount);
	ant_nums = NULL;
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

t_room		*ft_farm_alloc(t_room *farm, char **ant_nums, int *room_amount, int *ant_amount)
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

	*room_amount = ft_rooms(map, farm, ant_nums, line_amount);


	// farm[0].ant_index = ft_atoi(map[0]);
	// for (int j = 1; j < *room_amount; j++)
	// 	farm[j].ant_index = j + 1;

	// for (int j = 0; j < *room_amount; j++)
	// 	printf("%d\n", farm[j].ant_index);

	// while (1);

	return (farm);
	ant_nums = NULL;
	ant_amount = NULL;
}
