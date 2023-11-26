/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keybind_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:24:10 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:07:34 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	ft_print_movements(t_data *data)
{
	if (data->temp_dir != data->dir)
	{
		data->player->moves++;
		data->temp_dir = data->dir;
		ft_draw_movements(data);
	}
}

static void	get_keystroke(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if ((mlx_is_key_down(data->mlx, MLX_KEY_UP)
			|| mlx_is_key_down(data->mlx, MLX_KEY_W))
		&& data->player->x >= 0 && data->player->x < data->map->size_x / 32
		&& data->map->map[data->player->y - 1][data->player->x] != '1')
		data->dir = UP;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
			|| mlx_is_key_down(data->mlx, MLX_KEY_S))
		&& data->player->x >= 0 && data->player->x < data->map->size_x / 32
		&& data->map->map[data->player->y + 1][data->player->x] != '1')
		data->dir = DOWN;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
			|| mlx_is_key_down(data->mlx, MLX_KEY_A))
		&& data->player->y >= 0 && data->player->y < data->map->size_y / 32
		&& data->map->map[data->player->y][data->player->x - 1] != '1')
		data->dir = LEFT;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
			|| mlx_is_key_down(data->mlx, MLX_KEY_D))
		&& data->player->y >= 0 && data->player->y < data->map->size_y / 32
		&& data->map->map[data->player->y][data->player->x + 1] != '1')
		data->dir = RIGHT;
	ft_print_movements(data);
}

// if (data->player.x <= -1 && data->dir == LEFT)
// 	data->player.x = data->map.size_x / 32;
// else if (data->player.x >= data->map.size_x / 32 && data->dir == RIGHT)
// 	data->player.x = 0;
void	ft_keypress_helper(t_data	*data)
{
	if (data->dir == UP
		&& data->map->map[data->player->y - 1][data->player->x] != '1')
		data->player->y -= 1;
	else if (data->dir == DOWN
		&& data->map->map[data->player->y + 1][data->player->x] != '1')
		data->player->y += 1;
	else if (data->dir == LEFT
		&& data->map->map[data->player->y][data->player->x - 1] != '1')
		data->player->x -= 1;
	else if (data->dir == RIGHT
		&& data->map->map[data->player->y][data->player->x + 1] != '1')
		data->player->x += 1;
	if (data->map->map[data->player->y][data->player->x] == 'X')
		mlx_close_window(data->mlx);
	ft_render_player(data);
}

void	ft_keypress(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	get_keystroke(data);
	if (data->deceleration++ < 4)
		return ;
	data->deceleration = 0;
	ft_keypress_helper(data);
}
