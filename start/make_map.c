/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:41:09 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 21:24:48 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_map_start(char *content)
{
	char	*str;
	char	*save;

	str = content;
	save = str;
	while (*str)
	{
		if (*str == ' ' || *str == '1' || *str == '0')
			str++;
		else
			return (-1);
	}
	if (*str == '\0')
	{
		if (ft_strchr(save, '1') != NULL)
			return (1);
		else
			return (-1);
	}
	return (-1);
}

static void	get_map_size(t_data *data, t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	data->config->map_y = ft_strlen(tmp->content);
	data->config->map_x = 0;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->content) > data->config->map_y)
			data->config->map_y = ft_strlen(tmp->content);
		tmp = tmp->next;
		data->config->map_x += 1;
	}
}

int	make_map(t_list **head, int size, t_data *data)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	data->config->map = (char **)ft_calloc(size + 1, sizeof(char *));
	if (data->config->map == NULL)
	{
		ft_lstclear(head, NULL);
		message_error(5, data);
	}
	get_map_size(data, head);
	i = data->config->map_x - 1;
	while (tmp)
	{
		data->config->map[i--] = (tmp->content);
		tmp = tmp->next;
	}
	check_valid_map(data);
	start_game(data);
	return (1);
}
