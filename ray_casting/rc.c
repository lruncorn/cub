/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 13:35:28 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 12:04:26 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	turn_left_right(t_data *data, t_lodev *lodev)
{
	double	old_dir_x;
	double	old_plane_x;
	int		sign;

	sign = 1;
	if (data->keys->left == 1 || data->keys->right == 1)
	{
		if (data->player->flag_turn == 124)
			sign = -1;
		old_dir_x = lodev->dir.x;
		lodev->dir.x = old_dir_x * cos(0.05 * sign)
			 - lodev->dir.y * sin(0.05 * sign);
		lodev->dir.y = old_dir_x * sin(0.05 * sign)
			 + lodev->dir.y * cos(0.05 * sign);
		old_plane_x = lodev->plane.x;
		lodev->plane.x = old_plane_x * cos(0.05 * sign)
			 - lodev->plane.y * sin(0.05 * sign);
		lodev->plane.y = old_plane_x * sin(0.05 * sign)
			 + lodev->plane.y * cos(0.05 * sign);
	}
}

void	pre_rc(t_data *data, t_lodev *lodev, int i)
{
	lodev->hit = 0;
	lodev->camera.x = 2 * i / (double)data->config->r_x - 1;
	lodev->ray_dir.x = lodev->dir.x + lodev->plane.x * lodev->camera.x;
	lodev->ray_dir.y = lodev->dir.y + lodev->plane.y * lodev->camera.x;
	lodev->map.x = (int)data->player->x;
	lodev->map.y = (int)data->player->y;
	lodev->delta.x = fabs(1 / lodev->ray_dir.x);
	lodev->delta.y = fabs(1 / lodev->ray_dir.y);
}

int	ray_casting(t_data *data, t_lodev *lodev)
{
	int	i;
	int	line_height;

	i = 0;
	turn_left_right(data, lodev);
	move_player(data);
	while (i < data->config->r_x)
	{
		pre_rc(data, lodev, i);
		step_direction(data, lodev);
		hit_wall(data, lodev);
		no_fisheye_dist(data, lodev);
		line_height = find_line_height(data, lodev);
		draw_wall_slice_textured(data, lodev, line_height, i);
		data->lodev.wall_dist_save[i] = lodev->wall_dist;
		i++;
	}
	draw_sprites(data, data->lodev.wall_dist_save);
	return (1);
}
