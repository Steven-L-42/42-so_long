/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinding_helper_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:55:46 by slippert          #+#    #+#             */
/*   Updated: 2023/11/06 16:22:45 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	ft_fill_zirkular_straight(t_data *data, int *current_xy,
	int size_xy[2], int radius)
{
	*(current_xy + 0) += radius;
	if (*(current_xy + 0) < size_xy[0]
		&& data->path->map[*(current_xy + 1)][*(current_xy + 0)] == -1)
		data->path->map[*(current_xy + 1)][*(current_xy + 0)] = radius;
	*(current_xy + 1) += radius;
	*(current_xy + 0) -= radius;
	if (*(current_xy + 1) < size_xy[1] && *(current_xy + 0) >= 0
		&& data->path->map[*(current_xy + 1)][*(current_xy + 0)] == -1)
		data->path->map[*(current_xy + 1)][*(current_xy + 0)] = radius;
	*(current_xy + 1) -= radius;
	*(current_xy + 0) -= radius;
	if (*(current_xy + 1) >= 0 && *(current_xy + 0) >= 0
		&& data->path->map[*(current_xy + 1)][*(current_xy + 0)] == -1)
		data->path->map[*(current_xy + 1)][*(current_xy + 0)] = radius;
	*(current_xy + 1) -= radius;
	*(current_xy + 0) += radius;
	if (*(current_xy + 1) >= 0 && *(current_xy + 0) < size_xy[0]
		&& data->path->map[*(current_xy + 1)][*(current_xy + 0)] == -1)
		data->path->map[*(current_xy + 1)][*(current_xy + 0)] = radius;
}

static void	ft_fill_zirkular_diagonal(t_data *data, int *center_xy,
	int size_xy[2], int radius)
{
	if (*(center_xy + 1) - radius >= 0 && *(center_xy + 0) + radius < size_xy[0]
		&& data->path->map[*(center_xy + 1)
			- radius][*(center_xy + 0) + radius] == -1)
		data->path->map[*(center_xy + 1)
			- radius][*(center_xy + 0) + radius] = radius * 2;
	if (*(center_xy + 1) + radius < size_xy[1] && *(center_xy + 0) - radius >= 0
		&& data->path->map[*(center_xy + 1)
			+ radius][*(center_xy + 0) - radius] == -1)
		data->path->map[*(center_xy + 1)
			+ radius][*(center_xy + 0) - radius] = radius * 2;
	if (*(center_xy + 1) - radius >= 0 && *(center_xy + 0) - radius >= 0
		&& data->path->map[*(center_xy + 1)
			- radius][*(center_xy + 0) - radius] == -1)
		data->path->map[*(center_xy + 1)
			- radius][*(center_xy + 0) - radius] = radius * 2;
	if (*(center_xy + 1) + radius < size_xy[1]
		&& *(center_xy + 0) + radius < size_xy[0]
		&& data->path->map[*(center_xy + 1)
			+ radius][*(center_xy + 0) + radius] == -1)
		data->path->map[*(center_xy + 1)
			+ radius][*(center_xy + 0) + radius] = radius * 2;
}

static void	ft_fill_zirkular_missed(t_data *data, int center_xy[2],
	int size_xy[2], int xy[2])
{
	xy[1] = 0;
	while (xy[1] < size_xy[1])
	{
		xy[0] = 0;
		while (xy[0] < size_xy[0])
		{
			if (data->path->map[xy[1]][xy[0]] == -1)
				data->path->map[xy[1]][xy[0]]
					= ft_abs(center_xy[1] - xy[1])
					+ ft_abs(center_xy[0] - xy[0]);
			xy[0]++;
		}
		xy[1]++;
	}
}

static void	ft_fill_zirkular_reset(t_data *data, int xy[2],
	int size_xy[2], int center_xy[2])
{
	data->path->cycled++;
	if (data->path->cycled >= 24)
	{
		xy[1] = 0;
		data->path->cycled = 0;
		while (xy[1] < size_xy[1])
		{
			xy[0] = 0;
			while (xy[0] < size_xy[0])
			{
				if (data->map->map[xy[1]][xy[0]] == '1')
					data->path->map[xy[1]][xy[0]] = INT_MAX / 2;
				else
					data->path->map[xy[1]][xy[0]] = -1;
				xy[0]++;
			}
			xy[1]++;
		}
		data->path->map[center_xy[1]][center_xy[0]] = 0;
	}
}

void	ft_zirkular_pathfinding(t_data *data)
{
	int	radius;
	int	xy[2];
	int	size_xy[2];
	int	center_xy[2];
	int	current_xy[2];

	center_xy[0] = data->player->x;
	center_xy[1] = data->player->y;
	current_xy[0] = center_xy[0];
	current_xy[1] = center_xy[1];
	size_xy[0] = data->map->size_x / 32;
	size_xy[1] = data->map->size_y / 32;
	ft_fill_zirkular_reset(data, xy, size_xy, center_xy);
	radius = 1;
	while (radius <= size_xy[0] / 2)
	{
		current_xy[0] = center_xy[0];
		current_xy[1] = center_xy[1];
		ft_fill_zirkular_straight(data, current_xy, size_xy, radius);
		ft_fill_zirkular_diagonal(data, current_xy, size_xy, radius);
		radius++;
	}
	ft_fill_zirkular_missed(data, center_xy, size_xy, xy);
}
