/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:09:14 by vkuikka           #+#    #+#             */
/*   Updated: 2020/08/04 11:26:52 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// void	ft_add_link(t_links **list, int link_value)
// {
// 	t_links		*new;

// 	if (!(new = (t_links *)malloc(sizeof(t_links))))
// 		ft_error("memory allocation failed");
// 	new->link = link_value;
// 	new->first = list[0]->first;
// 	new->len = 0;
// 	new->next = NULL;
// 	list[0]->next = new;
// 	list[0] = new;
// }

// void	ft_new_list(t_links **link, int link_value)
// {
// 	if (!(link[0] = (t_links *)malloc(sizeof(t_links))))
// 		ft_error("memory allocation failed");
// 	link[0]->len = 0;
// 	link[0]->link = link_value;
// 	link[0]->first = link[0];
// 	link[0]->next = NULL;
// }

// int		ft_loop_links(t_links **link, int amount)
// {
// 	link[0] = link[0]->first;
// 	while (amount-- > 0)
// 	{
// 		if (!link[0]->next)
// 			return (0);
// 		link[0] = link[0]->next;
// 	}
// 	if (!link[0]->next)
// 		return (0);
// 	return (1);
// }