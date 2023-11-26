/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinding_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:55:46 by slippert          #+#    #+#             */
/*   Updated: 2023/11/06 16:22:18 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_pathfinding_calc_direction_helper(t_data *data,
	int pos_x[2], int pos_y[2])
{
	if ((pos_x[0] == pos_x[1] && pos_x[0] != INT_MAX / 2)
		|| (pos_y[0] == pos_y[1] && pos_y[0] != INT_MAX / 2)
		|| (pos_x[0] == pos_y[0] && pos_x[0] != INT_MAX / 2)
		|| (pos_x[0] == pos_y[1] && pos_x[0] != INT_MAX / 2)
		|| (pos_x[1] == pos_y[0] && pos_x[1] != INT_MAX / 2)
		|| (pos_x[1] == pos_y[1] && pos_x[1] != INT_MAX / 2))
	{
		if (data->ghosts->calc_x >= data->ghosts->calc_y)
		{
			data->ghosts->new_x += data->ghosts->is_pos_x * 32;
			data->path->map[data->ghosts->y][data->ghosts->new_x / 32]
				= INT_MAX / 2;
		}
		else
		{
			data->ghosts->new_y += data->ghosts->is_pos_y * 32;
			data->path->map[data->ghosts->new_y / 32][data->ghosts->x]
				= INT_MAX / 2;
		}
	}
}

void	ft_pathfinding_calc_direction(t_data *data, int pos_x[2], int pos_y[2])
{
	if (pos_x[0] < pos_x[1] && pos_x[0] < pos_y[0] && pos_x[0] < pos_y[1])
	{
		data->ghosts->new_x += 32;
		data->path->map[data->ghosts->y][data->ghosts->x + 1] = INT_MAX / 2;
	}
	else if (pos_x[1] < pos_x[0] && pos_x[1] < pos_y[0] && pos_x[1] < pos_y[1])
	{
		data->ghosts->new_x -= 32;
		data->path->map[data->ghosts->y][data->ghosts->x - 1] = INT_MAX / 2;
	}
	else if (pos_y[0] < pos_x[0] && pos_y[0] < pos_x[1] && pos_y[0] < pos_y[1])
	{
		data->ghosts->new_y += 32;
		data->path->map[data->ghosts->y + 1][data->ghosts->x] = INT_MAX / 2;
	}
	else if (pos_y[1] < pos_x[0] && pos_y[1] < pos_x[1] && pos_y[1] < pos_y[0])
	{
		data->ghosts->new_y -= 32;
		data->path->map[data->ghosts->y - 1][data->ghosts->x] = INT_MAX / 2;
	}
	else
		ft_pathfinding_calc_direction_helper(data, pos_x, pos_y);
}

void	ft_pathfinding_looking_for(t_data *data, int *pos_x, int *pos_y)
{
	if (data->path->map[data->ghosts->y][data->ghosts->x + 1]
		!= INT_MAX / 2)
		*pos_x = data->path->map[data->ghosts->y][data->ghosts->x + 1];
	else
		*pos_x = INT_MAX / 2;
	if (data->path->map[data->ghosts->y][data->ghosts->x - 1]
		!= INT_MAX / 2)
		*(pos_x + 1)
			= data->path->map[data->ghosts->y][data->ghosts->x - 1];
	else
		*(pos_x + 1) = INT_MAX / 2;
	if (data->path->map[data->ghosts->y + 1][data->ghosts->x]
		!= INT_MAX / 2)
		*pos_y = data->path->map[data->ghosts->y + 1][data->ghosts->x];
	else
		*pos_y = INT_MAX / 2;
	if (data->path->map[data->ghosts->y - 1][data->ghosts->x]
		!= INT_MAX / 2)
		*(pos_y + 1)
			= data->path->map[data->ghosts->y - 1][data->ghosts->x];
	else
		*(pos_y + 1) = INT_MAX / 2;
}

void	ft_update_ghost_position(t_data *data, int i)
{
	if (data->ghosts->new_x / 32 <= 0)
		data->ghosts->new_x = data->map->size_x - 64;
	else if (data->ghosts->new_x >= (data->map->size_x))
		data->ghosts->new_x = 32;
	if (data->map->map[data->ghosts->y][data->ghosts->x] != '1'
		&& data->map->map[data->ghosts->y][data->ghosts->x] != 'E')
		data->map->map[data->ghosts->y][data->ghosts->x] = '0';
	if (data->map->map[data->ghosts->new_y / 32][data->ghosts->new_x / 32]
		!= '1'
		&& data->map->map[data->ghosts->new_y / 32][data->ghosts->new_x / 32]
			!= 'E')
	{
		data->map->map[data->ghosts->new_y / 32][data->ghosts->new_x / 32]
			= 'X';
		data->ghosts->frame_left->instances[i].x = data->ghosts->new_x;
		data->ghosts->frame_right->instances[i].x = data->ghosts->new_x;
		data->ghosts->frame_left->instances[i].y = data->ghosts->new_y;
		data->ghosts->frame_right->instances[i].y = data->ghosts->new_y;
	}
}

void	ft_pathfinding(t_data *data, int i)
{
	int	pos_x[2];
	int	pos_y[2];

	ft_zirkular_pathfinding(data);
	ft_pathfinding_looking_for(data, pos_x, pos_y);
	data->path->map[data->ghosts->y][data->ghosts->x] += 1;
	ft_pathfinding_calc_direction(data, pos_x, pos_y);
	ft_update_ghost_position(data, i);
}
