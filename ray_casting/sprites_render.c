/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:44:36 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 19:49:14 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	sprite_put(t_data *data, int x, int y)
{
	int	color;

	data->texs->tex_y = (int)(256 * ((y
					 - (data->config->r_y - data->lodev.sprite_heigth) / 2)
				 * data->texs->sprite.height
				  / data->lodev.sprite_heigth)) / 256;
	color = my_pixel_get(&data->texs->sprite,
			 data->texs->tex_x, data->texs->tex_y);
	if (color != 0x000000)
		my_mlx_pixel_put(data, x, y, color);
}

void	draw_slice_sprite(t_data *data, double *wall_dist,
			 t_vector_int draw_start, t_vector_int draw_end)
{
	int	stripe;
	int	y;

	stripe = draw_start.x;
	while (stripe < draw_end.x)
	{
		data->texs->tex_x = (int)((stripe - (data->lodev.sprite_screen
						 - data->lodev.sprite_width / 2))
				 * data->texs->sprite.width / data->lodev.sprite_width);
		if (data->lodev.trans.y > 0 && data->lodev.trans.y < wall_dist[stripe]
			 && stripe > 0 && stripe < data->config->r_x)
		{
			y = draw_start.y;
			while (y < draw_end.y)
			{
				sprite_put(data, stripe, y);
				y++;
			}
		}
		stripe++;
	}
}

void	find_sprite_size(t_data *data, t_vector_int *draw_start,
	 t_vector_int *draw_end)
{
	data->lodev.sprite_heigth
		 = abs((int)(data->config->r_y / data->lodev.trans.y));
	draw_start->y = -data->lodev.sprite_heigth / 2 + data->config->r_y / 2;
	if (draw_start->y < 0)
		draw_start->y = 0;
	draw_end->y = data->lodev.sprite_heigth / 2 + data->config->r_y / 2;
	if (draw_end->y >= data->config->r_y)
		draw_end->y = data->config->r_y;
	data->lodev.sprite_width
		 = abs((int)(data->config->r_y / data->lodev.trans.y));
	draw_start->x = -data->lodev.sprite_width / 2 + data->lodev.sprite_screen;
	if (draw_start->x < 0)
		draw_start->x = 0;
	draw_end->x = data->lodev.sprite_width / 2 + data->lodev.sprite_screen;
	if (draw_end->x >= data->config->r_x)
		draw_end->x = data->config->r_x;
}

void	sprites_render(t_data *data, int i, double *wall_dist)
{
	double			inv_det;
	t_vector_int	draw_start;
	t_vector_int	draw_end;

	inv_det = 1.0 / (data->lodev.plane.x * data->lodev.dir.y
			 - data->lodev.dir.x * data->lodev.plane.y);
	data->lodev.trans.x = inv_det
		 * (data->lodev.dir.y * data->lodev.sprites[i]->res_x
			 - data->lodev.dir.x * data->lodev.sprites[i]->res_y);
	data->lodev.trans.y = inv_det * (data->lodev.plane.x
			* data->lodev.sprites[i]->res_y
			 - data->lodev.plane.y * data->lodev.sprites[i]->res_x);
	data->lodev.sprite_screen = (int)(data->config->r_x / 2 * (1
				 + data->lodev.trans.x / data->lodev.trans.y));
	find_sprite_size(data, &draw_start, &draw_end);
	draw_slice_sprite(data, wall_dist, draw_start, draw_end);
}
