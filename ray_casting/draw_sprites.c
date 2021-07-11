/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 09:40:55 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 11:59:37 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	sprite_sort(t_data *data)
{
	int			i;
	int			j;
	t_sprite	*save;

	i = 0;
	while (i < data->config->count_sprite - 1)
	{
		j = i + 1;
		while (j < data->config->count_sprite)
		{
			if (data->lodev.sprites[i]->dist < data->lodev.sprites[j]->dist)
			{
				save = data->lodev.sprites[i];
				data->lodev.sprites[i] = data->lodev.sprites[j];
				data->lodev.sprites[j] = save;
			}
			j++;
		}
		i++;
	}
}

void	sprite_dist(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config->count_sprite)
	{
		data->lodev.sprites[i]->res_x
			 = -data->player->x + data->lodev.sprites[i]->x;
		data->lodev.sprites[i]->res_y
			 = -data->player->y + data->lodev.sprites[i]->y;
		data->lodev.sprites[i]->dist
			 = data->lodev.sprites[i]->res_x
			 + data->lodev.sprites[i]->res_y * data->lodev.sprites[i]->res_y;
		i++;
	}
}

void	find_sprites(t_data *data)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	l = 0;
	if (data->lodev.sprites == NULL)
		message_error(2, data);
	while (data->config->map[i])
	{
		j = 0;
		while (data->config->map[i][j])
		{
			if (data->config->map[i][j] == '2')
			{
				data->lodev.sprites[l] = (t_sprite *)malloc(sizeof(t_sprite));
				data->lodev.sprites[l]->y = (double)i + 0.5;
				data->lodev.sprites[l]->x = (double)j + 0.5;
				l++;
			}
			j++;
		}
		i++;
	}
	data->lodev.sprites[l] = NULL;
}

void	draw_sprites(t_data *data, double *wall_dist)
{
	int	i;

	if (data->config->count_sprite == 0)
		return ;
	sprite_dist(data);
	sprite_sort(data);
	i = 0;
	while (i < data->config->count_sprite)
	{
		sprites_render(data, i, wall_dist);
		i++;
	}
}
