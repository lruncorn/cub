/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:11:19 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 16:42:39 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	get_bmp_header(t_bmp_file *info_bmp_file, t_data *data)
{
	info_bmp_file->byte_type[0] = 0x42;
	info_bmp_file->byte_type[1] = 0x4D;
	info_bmp_file->byte_size = (data->config->r_x * data->config->r_y * 4) + 54;
	info_bmp_file->byte_reserved = 0x00000000;
	info_bmp_file->byte_offset = 54;
	info_bmp_file->header_size = 40;
	info_bmp_file->image_width = data->config->r_x;
	info_bmp_file->image_height = -data->config->r_y;
	info_bmp_file->color_planes = 1;
	info_bmp_file->bits_per_pixel = 24;
	info_bmp_file->compression = 0;
	info_bmp_file->image_size = (data->config->r_x * data->config->r_y * 4);
	info_bmp_file->bits_xpels_per_meter = 2835;
	info_bmp_file->bits_xpels_per_meter = 2835;
	info_bmp_file->total_colors = 0;
	info_bmp_file->important_colors = 0;
}

static void	write_bmp(int fd, t_bmp_file info_bmp_file)
{
	write(fd, &info_bmp_file.byte_type, 2);
	write(fd, &info_bmp_file.byte_size, 4);
	write(fd, &info_bmp_file.byte_reserved, 4);
	write(fd, &info_bmp_file.byte_offset, 4);
	write(fd, &info_bmp_file.header_size, 4);
	write(fd, &info_bmp_file.image_width, 4);
	write(fd, &info_bmp_file.image_height, 4);
	write(fd, &info_bmp_file.color_planes, 2);
	write(fd, &info_bmp_file.bits_per_pixel, 2);
	write(fd, &info_bmp_file.compression, 4);
	write(fd, &info_bmp_file.image_size, 4);
	write(fd, &info_bmp_file.bits_xpels_per_meter, 4);
	write(fd, &info_bmp_file.bits_ypels_per_meter, 4);
	write(fd, &info_bmp_file.total_colors, 4);
	write(fd, &info_bmp_file.important_colors, 4);
}

static int	make_picture(int fd, t_data *data, int offset, int *adr)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;

	y = -1;
	ft_bzero(zero, 3);
	while (++y < data->config->r_y)
	{
		x = -1;
		while (++x < data->config->r_x)
		{
			pixel = *(adr + x + y * data->window->line_l / 4);
			write(fd, &pixel, 3);
		}
		if (offset > 0 && write(fd, &zero, offset) < 0)
			return (0);
	}
	return (1);
}

void	make_screenshot(t_data *data)
{
	t_bmp_file		bmp;
	int				offset;
	int				fd;
	int				*adr;

	adr = (int *)mlx_get_data_addr(data->window->img, &data->window->bpp,
			&data->window->line_l, &data->window->en);
	offset = (4 - ((int)data->config->r_x * 3) % 4) % 4;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT,
			0777 | O_TRUNC | O_APPEND);
	if (fd < 0)
		message_error(9, data);
	get_bmp_header(&bmp, data);
	write_bmp(fd, bmp);
	if (!(make_picture(fd, data, offset, adr)))
		message_error(9, data);
	close(fd);
	free_data(1, data);
	exit(0);
}
