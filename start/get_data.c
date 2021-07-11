/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:36:56 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 19:57:49 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_r(char **param, t_data *data, int *flag)
{
	int	i;

	if (data->config->r_x != -1)
		message_error(2, data);
	i = 0;
	while (param[i] != (void *)0)
		i++;
	if (i != 3)
		message_error(2, data);
	if (atoi_with_check(param[1], &data->config->r_x) == -1)
		message_error(2, data);
	if (atoi_with_check(param[2], &data->config->r_y) == -1)
		message_error(2, data);
	*flag = 1;
	return (1);
}

int	get_no(char **param, t_data *data, int *flag)
{
	int	i;

	if (data->config->no_path != NULL)
		message_error(2, data);
	i = 0;
	while (param[i])
		i++;
	if (i != 2)
		message_error(2, data);
	data->config->no_path = ft_strdup(param[1]);
	*flag = 1;
	return (1);
}

int	get_so(char **param, t_data *data, int *flag)
{
	int	i;

	i = 0;
	while (param[i] != (void *)0)
		i++;
	if (i != 2)
		message_error(2, data);
	data->config->so_path = ft_strdup(param[1]);
	*flag = 1;
	return (1);
}						

int	get_we(char **param, t_data *data, int *flag)
{
	int	i;

	i = 0;
	while (param[i] != (void *)0)
		i++;
	if (i != 2)
		message_error(2, data);
	data->config->we_path = ft_strdup(param[1]);
	*flag = 1;
	return (1);
}

int	get_ea(char **param, t_data *data, int *flag)
{
	int	i;

	i = 0;
	while (param[i] != (void *)0)
		i++;
	if (i != 2)
		message_error(2, data);
	data->config->ea_path = ft_strdup(param[1]);
	*flag = 1;
	return (1);
}
