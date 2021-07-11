/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:03:24 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:48:51 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	message_error(int error_number, t_data *data)
{
	if (error_number == 1)
		printf("%s\n", "Error\nCan't read config file.");
	if (error_number == 2)
		printf("%s\n", "Error\nWrong format of file.");
	if (error_number == 3)
		printf("%s\n", "Error\nWrong color RGB format.");
	if (error_number == 4)
		printf("%s\n", "Error\nCan't read the map, gnl error.");
	if (error_number == 5)
		printf("%s\n", "Error\nMemory allocation error.");
	if (error_number == 6)
		printf("%s\n", "Error\nNo map in configuration file.");
	if (error_number == 7)
		printf("%s\n", "Error\nNo map in configuration file.");
	if (error_number == 8)
		printf("%s\n", "Error\nInvalid map format.");
	if (error_number == 9)
		printf("%s\n", "Error\nWrong argument.");
	if (data != NULL)
		free_data(error_number, data);
	exit(0);
	return ;
}

void	free_next(t_data *data, int error_number)
{
	if (data->config->no_path != NULL)
		free(data->config->no_path);
	if (data->config->we_path != NULL)
		free(data->config->we_path);
	if (data->config->sprite_path != NULL)
		free(data->config->sprite_path);
	if (data->config->so_path != NULL)
		free(data->config->so_path);
	if (data->config->ea_path != NULL)
		free(data->config->ea_path);
	if (data->config != NULL)
		free(data->config);
	if (data->draw != NULL)
		free(data->draw);
	if (data->lodev.wall_dist_save != NULL && error_number > 8)
		free(data->lodev.wall_dist_save);
}

void	free_data(int error_number, t_data *data)
{
	if (error_number > 0)
	{
		if (data->config->map != NULL)
			free_mass(data->config->map);
		if (data->rgb != NULL)
			free_mass(data->rgb);
		if (data->rgb2 != NULL)
			free_mass(data->rgb2);
		if (data->window != NULL)
			free(data->window);
		if (data->player != NULL)
			free(data->player);
		if (data->keys != NULL)
			free(data->keys);
		if (data->texs != NULL)
			free(data->texs);
		free_next(data, error_number);
	}
}

void	free_mass(char **mass)
{
	char	**tmp;

	tmp = mass;
	while (mass && *mass)
		free(*mass++);
	free(tmp);
}

int	end_game(t_data *data)
{
	free_data(1, data);
	exit(0);
	return (1);
}
