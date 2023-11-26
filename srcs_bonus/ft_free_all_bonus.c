/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:32:00 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:53:50 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_i(int **arr, int size)
{
	if (!arr)
		return ;
	while (size-- > 0)
	{
		if (arr[size])
			free(arr[size]);
	}
	free(arr);
}

void	free_c(char **arr, int size)
{
	if (!arr)
		return ;
	while (size-- > 0)
	{
		if (arr[size])
			free(arr[size]);
		arr[size] = NULL;
	}
	free(arr);
}

void	free_both(char **data1, int **data2, int y)
{
	free_c(data1, y);
	free_i(data2, y);
}

void	free_single(void *item)
{
	if (!item)
		return ;
	free(item);
}

void	ft_freestuff(t_data *data, int sector)
{
	int	i;

	if (sector > 0)
	{
		free_c(data->map->map, data->map->size_y);
		free_c(data->map->coins_m, data->map->size_y);
		free_i(data->map->coins_i, data->map->size_y);
		free_i(data->path->map, data->map->size_y);
		mlx_delete_xpm42(data->text_coin);
		mlx_delete_xpm42(data->texture_wall);
		mlx_delete_xpm42(data->texture_background);
		i = 0;
		while (i < 6)
			mlx_delete_xpm42(data->player->text_frame_[i++]);
		mlx_delete_xpm42(data->texture_exit[0]);
		mlx_delete_xpm42(data->texture_exit[1]);
		mlx_delete_xpm42(data->ghosts->text_left);
		mlx_delete_xpm42(data->ghosts->text_right);
	}
	free_single(data->player);
	free_single(data->map);
	free_single(data->ghosts);
	free_single(data->path);
	free_single(data);
}
