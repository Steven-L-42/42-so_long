/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_text_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:13:06 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:17:46 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_draw_playername(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->img_playername)
		mlx_delete_image(data->mlx, data->img_playername);
	data->img_playername = mlx_put_string(data->mlx, "Paco",
			data->player->x * 32 - 5, data->player->y * 32 - 32);
}

void	ft_draw_movements(t_data *data)
{
	char		score[6];
	const char	*str_joined;
	const char	*str_nbr;

	score[0] = ' ';
	score[1] = 'M';
	score[2] = 'o';
	score[3] = 'v';
	score[4] = 'e';
	score[5] = '\0';
	str_nbr = (const char *)ft_itoa(data->player->moves);
	str_joined = (const char *)ft_strjoin(str_nbr, score);
	data->str_moves_nbr = (char *)str_nbr;
	data->str_moves_joined = (char *)str_joined;
	if (data->img_moves)
		mlx_delete_image(data->mlx, data->img_moves);
	data->img_moves = mlx_put_string(data->mlx, str_joined, 100, 6);
	free(data->str_moves_nbr);
	free(data->str_moves_joined);
}

void	ft_draw_scoreboard(void *param)
{
	t_data		*data;
	char		score[7];
	const char	*str_joined;
	const char	*str_nbr;

	score[0] = ' ';
	score[1] = 'C';
	score[2] = 'o';
	score[3] = 'i';
	score[4] = 'n';
	score[5] = 's';
	data = (t_data *)param;
	if (data->coins > data->coins_temp)
	{
		data->coins_temp = data->coins;
		str_nbr = (const char *)ft_itoa(data->coins);
		str_joined = (const char *)ft_strjoin(str_nbr, score);
		data->str_coins_nbr = (char *)str_nbr;
		data->str_coins_joined = (char *)str_joined;
		if (data->img_score)
			mlx_delete_image(data->mlx, data->img_score);
		data->img_score = mlx_put_string(data->mlx, str_joined, 8, 6);
		free(data->str_coins_nbr);
		free(data->str_coins_joined);
	}
}

void	set_credits(t_data *data)
{
	mlx_put_string(data->mlx, "developed by", 40,
		(data->map->size_y * 32) / 2 - 100);
	mlx_put_string(data->mlx, "Steven", 70,
		(data->map->size_y * 32) / 2 - 75);
}
