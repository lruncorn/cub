/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:54:37 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/24 20:00:18 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	step_direction(t_data *data, t_lodev *lodev)
{
	if (lodev->ray_dir.x < 0)
	{
		lodev->step.x = -1;
		lodev->side_dist.x = (data->player->x - lodev->map.x) * lodev->delta.x;
	}
	else
	{
		lodev->step.x = 1;
		lodev->side_dist.x = (lodev->map.x + 1.0
				 - data->player->x) * lodev->delta.x;
	}
	if (lodev->ray_dir.y < 0)
	{
		lodev->step.y = -1;
		lodev->side_dist.y = (data->player->y - lodev->map.y) * lodev->delta.y;
	}
	else
	{
		lodev->step.y = 1;
		lodev->side_dist.y = (lodev->map.y
				 + 1.0 - data->player->y) * lodev->delta.y;
	}
}

void	no_fisheye_dist(t_data *data, t_lodev *lodev)
{
	if (lodev->side == 0)
		lodev->wall_dist = (lodev->map.x
				 - data->player->x + (1 - lodev->step.x) / 2)
			  / lodev->ray_dir.x;
	else
		lodev->wall_dist = (lodev->map.y - data->player->y
				 + (1 - lodev->step.y) / 2) / lodev->ray_dir.y;
	if (lodev->wall_dist == 0)
		lodev->wall_dist += 0.5;
}

void	hit_wall(t_data *data, t_lodev *lodev)
{
	if (data->config->map[lodev->map.y][lodev->map.x] == '1')
		lodev->hit = 1;
	while (lodev->hit == 0)
	{
		if (lodev->side_dist.x < lodev->side_dist.y)
		{
			lodev->side_dist.x += lodev->delta.x;
			lodev->map.x += lodev->step.x;
			lodev->side = 0;
		}
		else
		{
			lodev->side_dist.y += lodev->delta.y;
			lodev->map.y += lodev->step.y;
			lodev->side = 1;
		}
		if (data->config->map[lodev->map.y][lodev->map.x] == '1')
		{
			lodev->hit = 1;
			break ;
		}
	}
}

int	find_line_height(t_data *data, t_lodev *lodev)
{
	int	result;

	result = 0;
	result = (int)(data->config->r_y / lodev->wall_dist);
	if (result > data->config->r_x)
		result = data->config->r_x;
	return (result);
}
