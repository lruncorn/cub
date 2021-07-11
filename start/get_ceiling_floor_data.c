/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling_floor_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:39:59 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:05:49 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_valid_rgb(int rgb)
{
	if (rgb > 255 || rgb < 0)
		return (-1);
	return (1);
}

int	get_f(char *content, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = content + 1;
	data->rgb = ft_split(tmp, ',');
	while (data->rgb[i])
		i++;
	if (i != 3)
		message_error(3, data);
	if (atoi_with_check(data->rgb[0], &data->config->f_r) == -1
		 || check_valid_rgb(data->config->f_r) == -1)
		message_error(3, data);
	if (atoi_with_check(data->rgb[1], &data->config->f_g) == -1
		 || check_valid_rgb(data->config->f_g) == -1)
		message_error(3, data);
	if (atoi_with_check(data->rgb[2], &data->config->f_b) == -1
		 || check_valid_rgb(data->config->f_g) == -1)
		message_error(3, data);
	return (1);
}

int	get_c(char *content, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = content + 1;
	data->rgb2 = ft_split(tmp, ',');
	while (data->rgb2[i])
		i++;
	if (i != 3)
		message_error(3, data);
	if (atoi_with_check(data->rgb2[0], &data->config->c_r) == -1
		|| check_valid_rgb(data->config->c_r) == -1)
		message_error(3, data);
	if (atoi_with_check(data->rgb2[1], &data->config->c_g) == -1
		|| check_valid_rgb(data->config->c_g) == -1)
		message_error(3, data);
	if (atoi_with_check(data->rgb2[2], &data->config->c_b) == -1
		|| check_valid_rgb(data->config->c_b) == -1)
		message_error(3, data);
	return (1);
}

void	get_c_f(char *content, t_data *data, int *flag)
{
	int	r;
	int	g;
	int	b;

	if (content[0] == 'C')
	{
		get_c(content, data);
		r = data->config->c_r;
		g = data->config->c_g;
		b = data->config->c_b;
		data->config->ceiling_color
			 = get_color_rgb(r, g, b);
		*flag = 1;
	}
	if (content[0] == 'F')
	{
		get_f(content, data);
		r = data->config->f_r;
		g = data->config->f_g;
		b = data->config->f_b;
		data->config->floor_color
			 = get_color_rgb(r, g, b);
		*flag = 1;
	}	
}

int	get_s(char **param, t_data *data, int *flag)
{
	int	i;

	i = 0;
	while (param[i] != (void *)0)
		i++;
	if (i != 2)
		message_error(2, data);
	data->config->sprite_path = ft_strdup(param[1]);
	*flag = 1;
	return (1);
}
