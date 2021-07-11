/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:18:39 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/25 12:52:20 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_color_rgb(int r, int g, int b)
{
	int	result;

	result = (r << 8) + g;
	result = (result << 8) + b;
	return (result);
}
