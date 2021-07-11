/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:14:51 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 15:08:57 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	window_init(t_data *data)
{
	data->window->mlx = NULL;
	data->window->img = NULL;
	data->window->addr = NULL;
}

int	render(t_data *data)
{
	if (data->flag != 1)
		mlx_do_sync(data->window->mlx);
	draw_floor_ceil(data);
	ray_casting(data, &data->lodev);
	if (data->flag != 1)
		mlx_put_image_to_window(data->window->mlx, data->window->win,
			 data->window->img, 0, 0);
	if (data->flag == 1)
		make_screenshot(data);
	return (0);
}

int	start_game(t_data *data)
{
	lodev_init(&data->lodev, data);
	data->lodev.wall_dist_save
		 = (double *)malloc(sizeof(double) * data->config->r_x);
	find_player(data);
	window_init(data);
	data->window->mlx = mlx_init();
	check_params(data);
	data->window->win
		 = mlx_new_window(data->window->mlx, data->config->r_x,
			 				 data->config->r_y, "cub3D");
	data->window->img = mlx_new_image(data->window->mlx,
			 data->config->r_x, data->config->r_y);
	data->window->addr = mlx_get_data_addr(data->window->img,
			 &data->window->bpp, &data->window->line_l, &data->window->en);
	start_rc(data);
	return (1);
}

int	start_rc(t_data *data)
{
	if (data->flag != 1)
	{
		mlx_hook(data->window->win, 17, 0, end_game, data);
		mlx_hook(data->window->win, 2, 0, press_key, data);
		mlx_hook(data->window->win, 3, 0, unpress_key, data);
	}
	init_texture(data);
	find_sprites(data);
	if (data->flag != 1)
	{
		mlx_loop_hook(data->window->mlx, render, data);
		mlx_loop(data->window->mlx);
	}
	if (data->flag == 1)
		render(data);
	return (1);
}
