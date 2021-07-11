/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 14:18:02 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 12:50:55 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	my_pixel_get(t_texture *tex, int x, int y)
{
	unsigned int	color;
	char			*dst;

	dst = tex->addr + (y * tex->ll + x * (tex->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

t_texture	*side_texture(t_data *data)
{
	if (data->lodev.side == 1)
	{
		if (data->lodev.ray_dir.y < 0)
			return (&data->texs->so);
		else
			return (&data->texs->no);
	}
	else
	{
		if (data->lodev.ray_dir.x < 0)
			return (&data->texs->ea);
		else
			return (&data->texs->we);
	}
}

void	find_draw_start_end(t_data *data, t_draw *draw, int height)
{
	draw->draw_start = (data->config->r_y - height) / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = (height + data->config->r_y) / 2;
	if (draw->draw_end >= data->config->r_y)
		draw->draw_end = data->config->r_y - 1;
}

void	calc_texture(t_lodev *lodev, t_data *data, t_draw *draw, t_texture *tex)
{
	if (lodev->side == 0)
		draw->wall_x = data->player->y + lodev->wall_dist * lodev->ray_dir.y;
	else
		draw->wall_x = data->player->x + lodev->wall_dist * lodev->ray_dir.x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (double)tex->width);
	if (lodev->side == 1 && lodev->ray_dir.y < 0)
		draw->tex_x = tex->width - draw->tex_x - 1;
	if (lodev->side == 0 && lodev->ray_dir.x > 0)
		draw->tex_x = tex->width - draw->tex_x - 1;
}

void	draw_wall_slice_textured(t_data *data, t_lodev *lodev,
			 int height, int x)
{
	t_draw		*draw;
	t_texture	*tex;

	draw = data->draw;
	draw->y = 0;
	tex = side_texture(data);
	find_draw_start_end(data, draw, height);
	calc_texture(lodev, data, draw, tex);
	draw->step_tex = 1.0 * tex->height / height;
	draw->tex_pos = (draw->draw_start - data->config->r_y
			 / 2 + height / 2) * draw->step_tex;
	draw->y = draw->draw_start;
	while (draw->y < draw->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos & (tex->height - 1);
		draw->tex_pos += draw->step_tex;
		draw->color = my_pixel_get(tex, draw->tex_x, draw->tex_y);
		my_mlx_pixel_put(data, x, draw->y, draw->color);
		draw->y++;
	}
}
