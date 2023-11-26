/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:15:43 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 15:59:35 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	init_load_images_helper(t_data *data)
{
	int		i;
	char	*path_summary[4];
	char	*number;

	path_summary[0] = ft_strdup("textures/player_00");
	path_summary[2] = ft_strdup(".xpm42");
	i = 0;
	while (i < 6)
	{
		number = ft_itoa(i + 1);
		path_summary[1] = ft_strjoin(path_summary[0], number);
		path_summary[3] = ft_strjoin(path_summary[1], path_summary[2]);
		data->player->text_frame_[i] = mlx_load_xpm42(path_summary[3]);
		free(number);
		free(path_summary[1]);
		free(path_summary[3]);
		if (!data->player->text_frame_[i])
			return (1);
		i++;
	}
	free(path_summary[0]);
	free(path_summary[2]);
	return (0);
}

int	init_load_images(t_data *data)
{
	if (init_load_images_helper(data))
		return (0);
	data->texture_background = mlx_load_xpm42("textures/bg.xpm42");
	if (!data->texture_background)
		return (0);
	data->texture_wall = mlx_load_xpm42("textures/wall.xpm42");
	if (!data->texture_wall)
		return (0);
	data->text_coin = mlx_load_xpm42("textures/coin.xpm42");
	if (!data->text_coin)
		return (0);
	data->ghosts->text_left = mlx_load_xpm42("textures/ghost_left.xpm42");
	if (!data->ghosts->text_left)
		return (0);
	data->ghosts->text_right = mlx_load_xpm42("textures/ghost_right.xpm42");
	if (!data->ghosts->text_right)
		return (0);
	data->texture_exit[0] = mlx_load_xpm42("textures/exit_0.xpm42");
	if (!data->texture_exit[0])
		return (0);
	data->texture_exit[1] = mlx_load_xpm42("textures/exit_1.xpm42");
	if (!data->texture_exit[1])
		return (0);
	return (1);
}
