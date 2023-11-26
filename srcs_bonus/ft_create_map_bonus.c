/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:17:04 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:48:32 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_map_wall_floor(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x] && data->map->map[y][x] != '\n')
		{
			if (data->map->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->game_wall, x * 32, y * 32);
			else
				mlx_image_to_window(data->mlx, data->game_bg, x * 32, y * 32);
			if (data->map->map[y][x] == 'E')
			{
				mlx_image_to_window(data->mlx, data->img_exit[1],
					x * 32, y * 32);
				mlx_image_to_window(data->mlx, data->img_exit[0],
					x * 32, y * 32);
			}
			x++;
		}
		y++;
	}
}

static void	init_map_coins_helper(t_data *data, int x, int y)
{
	if (data->map->map[y][x] == 'C')
	{
		data->map->coins_m[y][x] = 'C';
		data->map->coins_i[y][x] = mlx_image_to_window(data->mlx,
				data->game_coin, x * 32, y * 32);
	}
}

int	init_map_coins(t_data *data)
{
	int		x;
	int		y;

	data->map->coins_i = ft_calloc(data->map->size_y + 1, sizeof(int *));
	data->map->coins_m = ft_calloc(data->map->size_y + 1, sizeof(char *));
	if (!data->map->coins_i || !data->map->coins_m)
		return (free_both(data->map->coins_m, data->map->coins_i, 0), 0);
	y = 0;
	while (y < data->map->size_y)
	{
		data->map->coins_i[y] = ft_calloc(data->map->size_x + 1, sizeof(int));
		data->map->coins_m[y] = ft_calloc(data->map->size_x + 1, sizeof(char));
		if (!data->map->coins_i[y] || !data->map->coins_m[y])
			return (free_both(data->map->coins_m, data->map->coins_i, y), 0);
		y++;
	}
	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x] && data->map->map[y][x] != '\n')
			init_map_coins_helper(data, x++, y);
		y++;
	}
	return (1);
}

static void	init_map_ghosts_helper(t_data *data, int x, int y)
{
	mlx_image_to_window(data->mlx, data->ghosts->frame_right,
		x * 32, y * 32);
	mlx_image_to_window(data->mlx, data->ghosts->frame_left,
		x * 32, y * 32);
	data->ghosts->frame_left->instances[data->ghosts->count].x
		= x * 32;
	data->ghosts->frame_right->instances[data->ghosts->count].x
		= x * 32;
	data->ghosts->frame_right->instances[data->ghosts->count].y
		= y * 32;
	data->ghosts->frame_left->instances[data->ghosts->count].y
		= y * 32;
	data->ghosts->count++;
}

void	init_map_ghosts(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	data->ghosts->count = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x] && data->map->map[y][x] != '\n')
		{
			if (data->map->map[y][x] == 'X')
				init_map_ghosts_helper(data, x, y);
			x++;
		}
		y++;
	}
	data->map->map[y] = NULL;
}
