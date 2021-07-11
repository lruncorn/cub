/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:12:35 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 19:49:05 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->config->map[i])
	{
		j = 0;
		while (data->config->map[i][j])
		{
			if (data->config->map[i][j] == 'N'
			 || data->config->map[i][j] == 'S' ||
				data->config->map[i][j] == 'W' ||
				 data->config->map[i][j] == 'E')
			{
				data->player->y = (double)i + 0.5;
				data->player->x = (double)j + 0.5;
				data->player->orientation = data->config->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

int	no_wall(t_data *data, int dir, int step)
{
	if (dir == 'y')
	{
		if ((int)(data->player->y + step * data->lodev.dir.y)
			 >= (int)data->config->map_x
			  || (int)(data->player->y + step * data->lodev.dir.y) == 1)
			return (0);
		if (data->config->map[(int)(data->player->y
				 + step * data->lodev.dir.y)][(int)data->player->x] == '1')
			return (0);
	}
	if (dir == 'x')
	{
		if ((int)(data->player->x
			 + step * data->lodev.dir.x) >= (int)data->config->map_y)
			return (0);
		if (data->config->map[(int)data->player->y][(int)(data->player->x
			 + step * data->lodev.dir.x)] == '1')
			return (0);
	}
	return (1);
}

int	no_wall_ad(t_data *data, int dir, int step)
{
	if (dir == 'y')
	{
		if ((int)(data->player->y + step * -data->lodev.dir.x)
		 >= (int)data->config->map_x
		  || (int)(data->player->y + step * -data->lodev.dir.x) == 1)
			return (0);
		if (data->config->map[(int)(data->player->y
				 + step * -data->lodev.dir.x)][(int)data->player->x] == '1')
			return (0);
	}
	if (dir == 'x')
	{
		if ((int)(data->player->x
			 + step * data->lodev.dir.y) >= (int)data->config->map_y)
			return (0);
		if (data->config->map[(int)data->player->y][(int)(data->player->x
			 + step * data->lodev.dir.y)] == '1')
			return (0);
	}
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->window->addr + (y * data->window->line_l
			 + x * (data->window->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceil(t_data *data)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	x = 0;
	while (y < data->config->r_y)
	{
		x = 0;
		color = data->config->ceiling_color;
		if (y > data->config->r_y / 2)
			color = data->config->floor_color;
		while (x < data->config->r_x)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}
