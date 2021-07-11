/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 12:19:31 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 12:42:21 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_texture(t_texture *tex, t_data *data)
{
	if (tex->img == NULL)
		message_error(2, data);
}

void	init_next_textures(t_data *data)
{
	data->texs->we.img
		 = mlx_png_file_to_image(data->window->mlx, data->config->we_path,
			&data->texs->we.width, &data->texs->we.height);
	check_texture(&data->texs->we, data);
	data->texs->we.addr
		 = mlx_get_data_addr(data->texs->we.img, &data->texs->we.bpp,
			 					&data->texs->we.ll, &data->texs->we.end);
	data->texs->ea.img
		 = mlx_png_file_to_image(data->window->mlx, data->config->ea_path,
			 							&data->texs->ea.width,
			&data->texs->ea.height);
	check_texture(&data->texs->ea, data);
	data->texs->ea.addr
		 = mlx_get_data_addr(data->texs->ea.img, &data->texs->ea.bpp,
			 			&data->texs->ea.ll, &data->texs->ea.end);
	data->texs->sprite.img
		 = mlx_png_file_to_image(data->window->mlx, data->config->sprite_path,
			  &data->texs->sprite.width, &data->texs->sprite.height);
	check_texture(&data->texs->sprite, data);
	data->texs->sprite.addr
		 = mlx_get_data_addr(data->texs->sprite.img, &data->texs->sprite.bpp,
			 			 &data->texs->sprite.ll, &data->texs->sprite.end);
}

void	init_texture(t_data *data)
{
	data->texs->no.img
		= mlx_png_file_to_image(data->window->mlx,
			data->config->no_path,
			&data->texs->no.width, &data->texs->no.height);
	check_texture(&data->texs->no, data);
	data->texs->no.addr
		 = mlx_get_data_addr(data->texs->no.img, &data->texs->no.bpp,
			 	 &data->texs->no.ll, &data->texs->no.end);
	data->texs->so.img
		 = mlx_png_file_to_image(data->window->mlx, data->config->so_path,
			 				 &data->texs->so.width, &data->texs->so.height);
	check_texture(&data->texs->so, data);
	data->texs->so.addr
		 = mlx_get_data_addr(data->texs->so.img, &data->texs->so.bpp,
			  &data->texs->so.ll, &data->texs->so.end);
	init_next_textures(data);
}
