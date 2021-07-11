/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 13:51:01 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 20:12:48 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	read_file(int fd, t_data *data)
{
	char	*line;
	t_list	*head;

	head = NULL;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
		data->config->line_count += 1;
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	data->config->line_count += 1;
	parse_config(head, data);
}

int	read_config_file(char *name, t_data *data)
{
	int	fd;

	if (check_name(name) == 1)
	{
		fd = open(name, O_RDONLY);
		if (!fd)
			message_error(1, NULL);
		else
			read_file(fd, data);
	}
	else
		message_error(9, data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	init_config(&data);
	data.flag = 0;
	if (argc == 2)
		read_config_file(argv[1], &data);
	if (argc == 3 && (ft_strcmp(argv[2], "--save") == 1))
	{
		data.flag = 1;
		read_config_file(argv[1], &data);
	}
}
