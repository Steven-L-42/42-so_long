/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:17:59 by slippert          #+#    #+#             */
/*   Updated: 2023/11/11 09:50:31 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

static int	ft_check_wall_surrounded(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		if (data->map->map[y][x] != '1')
			return (0);
		while (data->map->map[y][x])
			x++;
		if (data->map->map[y][data->map->size_x / 32 - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	ft_error_handling_helper(t_data *data)
{
	if (data->map->co_ex[0] != 0 || data->map->co_ex[1] > 0)
		return (ft_printf
			("Error\nSome coins or the exit cannot be reached!\n"), 0);
	if (data->wrong_characters >= 1)
		return (ft_printf
			("Error\nFile contains not allowed characters!\n"), 0);
	return (1);
}

int	ft_error_handling(t_data *data, int x_cmp, int x_y[2])
{
	if (data->map->map[x_y[1] - 1][x_y[0] - 1] == '\n')
		return (ft_printf
			("Error\nFile contains new Lines at end!\n"), 0);
	if (x_cmp < 0)
		return (ft_printf
			("Error\nFile width not on all spots correct!\n"), 0);
	if (!ft_check_wall_surrounded(data))
		return (ft_printf
			("Error\nMap have to be fully surrounded by walls!\n"), 0);
	if (data->player->count != 1)
		return (ft_printf
			("Error\nFile contains less or more than 1 Player!\n"), 0);
	if (data->map->count_exit < 1 || data->map->count_exit > 1)
		return (ft_printf
			("Error\nFile contains less or more than 1 exit!\n"), 0);
	if (data->map->count_space == 0)
		return (ft_printf
			("Error\nFile contains less than 1 space!\n"), 0);
	if (data->collectibles_count == 0)
		return (ft_printf
			("Error\nFile contains less than 1 collectible!\n"), 0);
	if (!ft_error_handling_helper(data))
		return (0);
	return (1);
}
