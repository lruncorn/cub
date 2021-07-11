/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:51:34 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:12:24 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	parse_config(t_list *head, t_data *data)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (check_map_start(tmp->content) == 1)
		{
			make_map(&tmp, ft_lstsize(tmp), data);
			return (1);
		}
		get_data(tmp->content, data);
		tmp = tmp->next;
	}
	message_error(6, data);
	return (-1);
}

int	ft_strcmp(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (*str1)
	{
		if (*str1 != *str2)
			return (-1);
		str1++;
		str2++;
	}
	return (1);
}

int	get_next_data(char **param, t_data *data, int *flag, char *content)
{
	if (ft_strcmp(param[0], "WE") == 1)
		get_we(param, data, flag);
	if (ft_strcmp(param[0], "EA") == 1)
		get_ea(param, data, flag);
	if (ft_strcmp(param[0], "S") == 1)
		get_s(param, data, flag);
	if (ft_strcmp(param[0], "C") == 1)
		get_c_f(content, data, flag);
	if (ft_strcmp(param[0], "F") == 1)
		get_c_f(content, data, flag);
	return (1);
}

int	get_data(char *content, t_data *data)
{
	char	*str;
	char	**param;
	int		flag;

	flag = 0;
	str = content;
	if (*str == '\0')
		return (1);
	param = ft_split(str, ' ');
	if (ft_strcmp(param[0], "R") == 1)
		get_r(param, data, &flag);
	if (ft_strcmp(param[0], "NO") == 1)
		get_no(param, data, &flag);
	if (ft_strcmp(param[0], "SO") == 1)
		get_so(param, data, &flag);
	get_next_data(param, data, &flag, content);
	if (flag == 1)
		free_mass(param);
	return (1);
}
