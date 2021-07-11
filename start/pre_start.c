/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:08:41 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:13:29 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_params(t_data *data)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(data->window->mlx, &screen_width, &screen_height);
	if (data->config->r_x > screen_width)
		data->config->r_x = screen_width - 1;
	if (data->config->r_y > screen_height)
		data->config->r_y = screen_height - 1;
}
