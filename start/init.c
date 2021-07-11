/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:41:54 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:45:27 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_data(t_data *data)
{
	data->window = (t_window *)malloc(sizeof(t_window));
	data->player = (t_player *)malloc(sizeof(t_player));
	data->keys = (t_keys *)malloc(sizeof(t_keys));
	data->texs = (t_texs *)malloc(sizeof(t_texs));
	data->draw = (t_draw *)malloc(sizeof(t_draw));
	data->keys->left = 0;
	data->keys->right = 0;
	data->player->flag_turn = -1;
}

void	init_ns(t_lodev *lodev, t_data *data)
{
	if (data->config->player == 'S')
	{
		lodev->dir.x = 0;
		lodev->dir.y = -1;
		lodev->plane.x = -0.66;
		lodev->plane.y = 0;
	}
	if (data->config->player == 'N')
	{
		lodev->dir.x = 0;
		lodev->dir.y = 1;
		lodev->plane.x = 0.66;
		lodev->plane.y = 0;
	}
}

void	lodev_init(t_lodev *lodev, t_data *data)
{
	data->lodev.sprites = (t_sprite **)malloc
		(sizeof(t_sprite *) * (data->config->count_sprite + 1));
	if (data->config->player == 'N' || data->config->player == 'S')
		init_ns(lodev, data);
	if (data->config->player == 'E')
	{
		lodev->dir.x = 1;
		lodev->dir.y = 0;
		lodev->plane.x = 0;
		lodev->plane.y = -0.66;
	}
	if (data->config->player == 'W')
	{
		lodev->dir.x = -1;
		lodev->dir.y = 0;
		lodev->plane.x = 0;
		lodev->plane.y = 0.66;
	}	
}

void	init_config(t_data *data)
{
	data->config = (t_config *)malloc(sizeof(t_config));
	data->config->no_path = NULL;
	data->config->so_path = NULL;
	data->config->we_path = NULL;
	data->config->ea_path = NULL;
	data->config->sprite_path = NULL;
	data->config->f_r = -1;
	data->config->f_g = -1;
	data->config->f_b = -1;
	data->config->c_r = -1;
	data->config->c_g = -1;
	data->config->c_b = -1;
	data->config->map = NULL;
	data->config->map_x = -1;
	data->config->map_y = -1;
	data->config->line_count = 0;
	data->config->r_x = -1;
	data->config->r_y = -1;
	data->config->count_sprite = 0;
	data->config->player = '0';
	data->config->floor_color = -1;
	data->config->ceiling_color = -1;
}
