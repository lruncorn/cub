/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:18:14 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 21:21:52 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (-1);
}

void	check_inside_map(t_data *data, int i, int j)
{
	if (i == 0 || (size_t)j == ft_strlen(data->config->map[i]))
		message_error(8, data);
	if (data->config->map[i][j + 1] == ' '
		 || data->config->map[i][j + 1] == '\0')
		message_error(8, data);
	if (data->config->map[i][j - 1] == ' '
		 || data->config->map[i][j - 1] == '\0')
		message_error(8, data);
	if (data->config->map[i + 1][j] == ' '
		 || data->config->map[i + 1][j] == '\0')
		message_error(8, data);
	if (data->config->map[i - 1][j] == ' '
		 || data->config->map[i - 1][j] == '\0')
		message_error(8, data);
	if (data->config->map[i][j] == '2')
		data->config->count_sprite += 1;
	if (is_player(data->config->map[i][j]) == 1)
	{
		if (data->config->player != '0')
			message_error(8, data);
		data->config->player = data->config->map[i][j];
	}
}

void	check_map(t_data *data, int i, int j)
{
	if (data->config->map[i][j] == '0' || data->config->map[i][j] == '2'
			 || is_player(data->config->map[i][j]) == 1)
		check_inside_map(data, i, j);
	else if (data->config->map[i][j] != '1' && data->config->map[i][j] != ' ')
		message_error (8, data);
}

void	check_valid_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->config->map[i])
	{
		j = 0;
		if (data->config->map[i][j] == '\0' && i != 0)
			message_error(8, data);
		while (data->config->map[i][j])
		{
			check_map(data, i, j);
			j++;
		}
		i++;
	}
	if (data->config->player == '0')
		message_error(8, data);
}
