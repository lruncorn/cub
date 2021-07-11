/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lruncorn <lruncorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:05:37 by lruncorn          #+#    #+#             */
/*   Updated: 2021/04/26 12:07:26 by lruncorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (-1);
}

int	atoi_with_check(const char *str, int *res)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (is_space(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	while (is_space(*str) == 1)
		str++;
	if (*str != '\0')
		return (-1);
	result *= sign;
	if (result > INT_MAX || result < INT_MIN)
		return (-1);
	*res = result;
	return (1);
}

int	check_name(char *name)
{
	char	*dot_pointer;

	dot_pointer = ft_strchr(name, '.');
	if (dot_pointer == NULL)
		return (-1);
	else
	{
		if (ft_strncmp(dot_pointer, ".cub", ft_strlen(dot_pointer)) == 0
			&& ft_strlen(dot_pointer) == 4)
			return (1);
		else
			return (-1);
	}
	return (1);
}
