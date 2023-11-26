/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_one_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:15:43 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:09:19 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	init_texture_to_image_helper(t_data *data)
{
	data->game_bg
		= mlx_texture_to_image(data->mlx, &data->texture_background->texture);
	if (!data->game_bg)
		return (0);
	data->ghosts->frame_left
		= mlx_texture_to_image(data->mlx, &data->ghosts->text_left->texture);
	if (!data->ghosts->frame_left)
		return (0);
	data->ghosts->frame_right
		= mlx_texture_to_image(data->mlx, &data->ghosts->text_right->texture);
	if (!data->ghosts->frame_right)
		return (0);
	data->img_exit[0]
		= mlx_texture_to_image(data->mlx, &data->texture_exit[0]->texture);
	if (!data->img_exit[0])
		return (0);
	data->img_exit[1]
		= mlx_texture_to_image(data->mlx, &data->texture_exit[1]->texture);
	if (!data->img_exit[1])
		return (0);
	return (1);
}

static int	init_texture_to_image(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		data->player->frame_[i] = mlx_texture_to_image(data->mlx,
				&data->player->text_frame_[i]->texture);
		if (!data->player->frame_[i])
			return (0);
		i++;
	}
	data->game_coin
		= mlx_texture_to_image(data->mlx, &data->text_coin->texture);
	if (!data->game_coin)
		return (0);
	data->game_wall
		= mlx_texture_to_image(data->mlx, &data->texture_wall->texture);
	if (!data->game_wall)
		return (0);
	if (!init_texture_to_image_helper(data))
		return (0);
	return (1);
}

void	init_loop_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, ft_draw_playername, (void *)data);
	mlx_loop_hook(data->mlx, ft_draw_scoreboard, (void *)data);
	mlx_loop_hook(data->mlx, ft_keypress, (void *)data);
	mlx_loop_hook(data->mlx, ft_ghost_movement, (void *)data);
}

static void	init_layers(t_data *data)
{
	mlx_image_to_window(data->mlx, data->player->frame_[0],
		data->player->x * 32, data->player->y * 32);
	mlx_image_to_window(data->mlx, data->player->frame_[1],
		data->player->x * 32, data->player->y * 32);
	mlx_image_to_window(data->mlx, data->player->frame_[2],
		data->player->x * 32, data->player->y * 32);
	mlx_image_to_window(data->mlx, data->player->frame_[3],
		data->player->x * 32, data->player->y * 32);
	mlx_image_to_window(data->mlx, data->player->frame_[4],
		data->player->x * 32, data->player->y * 32);
	mlx_image_to_window(data->mlx, data->player->frame_[5],
		data->player->x * 32, data->player->y * 32);
}

int	init_summary(t_data *data)
{
	data->mlx = mlx_init(data->map->size_x, data->map->size_y, "PaceoManeo", 0);
	if (!data->mlx)
		return (0);
	if (!init_load_images(data))
		return (0);
	if (!init_texture_to_image(data))
		return (0);
	init_map_wall_floor(data);
	if (!init_map_coins(data))
		return (0);
	init_map_ghosts(data);
	init_layers(data);
	data->player->moves = -1;
	data->ghosts->active_frame = 1;
	data->ghosts->deceleration_ghost = 0;
	data->player->frame = 0;
	data->deceleration = 0;
	data->coins = 0;
	data->frame_dir = 1;
	data->coins_temp = -1;
	data->path->cycled = 24;
	return (1);
}
