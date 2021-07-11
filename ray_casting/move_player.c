/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:14:02 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/24 21:41:38 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_ad(t_data *data, int step)
{
	if (data->keys->a == 1)
		step *= -1;
	if (no_wall_ad(data, 'y', step))
		data->player->y += step * -data->lodev.dir.x;
	if (no_wall_ad(data, 'x', step))
		data->player->x += step * data->lodev.dir.y;
	data->keys->a = 0;
	data->keys->d = 0;
}

void	move_player(t_data *data)
{
	int	step;

	step = 1;
	if (data->keys->w == 1)
	{
		if (no_wall(data, 'y', step))
			data->player->y += step * data->lodev.dir.y;
		if (no_wall(data, 'x', step))
			data->player->x += step * data->lodev.dir.x;
		data->keys->w = 0;
	}	
	if (data->keys->s == 1)
	{
		step *= -1;
		if (no_wall(data, 'y', step))
			data->player->y += step * data->lodev.dir.y;
		if (no_wall(data, 'x', step))
			data->player->x += step * data->lodev.dir.x;
		data->keys->s = 0;
	}
	if (data->keys->a == 1 || data->keys->d == 1)
		move_ad(data, step);
}

int	press_key(int	keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->window->mlx, data->window->win);
		exit (0);
	}
	if (keycode == 123)
	{
		data->player->flag_turn = 123;
		data->keys->left = 1;
	}
	if (keycode == 124)
	{
		data->player->flag_turn = 124;
		data->keys->right = 1;
	}
	if (keycode == 1)
		data->keys->s = 1;
	if (keycode == 13)
		data->keys->w = 1;
	if (keycode == 0)
		data->keys->a = 1;
	if (keycode == 2)
		data->keys->d = 1;
	return (1);
}

int	unpress_key(int	keycode, t_data *data)
{
	if (keycode == 123)
	{
		data->player->flag_turn = 0;
		data->keys->left = 0;
	}
	if (keycode == 124)
	{
		data->player->flag_turn = 124;
		data->keys->right = 0;
	}
	if (keycode == 1)
		data->keys->s = 0;
	if (keycode == 13)
		data->keys->w = 0;
	if (keycode == 0)
		data->keys->a = 0;
	if (keycode == 2)
		data->keys->d = 0;
	return (1);
}
