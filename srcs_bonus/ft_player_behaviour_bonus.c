/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_behaviour_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:27:21 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:41:33 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	ft_set_active_layer(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (i == data->player->frame)
			data->player->frame_[i]->instances[0].enabled = 1;
		else
			data->player->frame_[i]->instances[0].enabled = 0;
		i++;
	}
}

// i = 0;
// 	while (data->img_exit[0]->instances[i].enabled)
// 	{
// 		data->img_exit[0]->instances[i].enabled = 0;
// 		i++;
// 	}
static void	ft_check_for_collectible(t_data *data)
{
	if (data->map->coins_m[data->player->y][data->player->x] == 'C')
	{
		data->map->coins_m[data->player->y][data->player->x] = '0';
		data->game_coin->instances[data->map->coins_i
		[data->player->y][data->player->x]].enabled = 0;
		data->coins++;
		if (data->coins >= data->collectibles_count)
			data->img_exit[0]->instances[0].enabled = 0;
		data->map->map[data->player->y][data->player->x] = '0';
	}
}

void	ft_render_player(t_data *data)
{
	int	i;

	ft_set_active_layer(data);
	if (data->frame_dir)
		data->player->frame++;
	else
		data->player->frame--;
	if (data->player->frame >= 5 && data->frame_dir == 1)
		data->frame_dir = 0;
	if (data->player->frame <= 0 && data->frame_dir == 0)
		data->frame_dir = 1;
	i = 0;
	while (i < 6)
	{
		data->player->frame_[i]->instances[0].x = data->player->x * 32;
		data->player->frame_[i]->instances[0].y = data->player->y * 32;
		i++;
	}
	if (data->map->map[data->player->y][data->player->x] == 'E'
		&& data->coins == data->collectibles_count)
		mlx_close_window(data->mlx);
	ft_check_for_collectible(data);
}
