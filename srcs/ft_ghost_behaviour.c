/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ghost_behaviour.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:21:21 by slippert          #+#    #+#             */
/*   Updated: 2023/11/01 13:00:21 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	ft_set_ghost_variables(t_data *data, int i)
{
	data->ghosts->new_x = data->ghosts->frame_left->instances[i].x;
	data->ghosts->new_y = data->ghosts->frame_left->instances[i].y;
	data->ghosts->x = data->ghosts->new_x / 32;
	data->ghosts->y = data->ghosts->new_y / 32;
	data->ghosts->calc_x = data->player->x - data->ghosts->x;
	data->ghosts->calc_y = data->ghosts->y - data->player->y;
	data->ghosts->is_pos_x = 1;
	data->ghosts->is_pos_y = -1;
	if (data->ghosts->calc_x < 0)
		data->ghosts->is_pos_x = -1;
	if (data->ghosts->calc_y < 0)
		data->ghosts->is_pos_y = 1;
}

void	ft_ghost_movement(void *param)
{
	int		i;
	t_data	*data;

	data = (t_data *)param;
	data->ghosts->deceleration_ghost++;
	if (data->ghosts->deceleration_ghost < 6)
		return ;
	data->ghosts->deceleration_ghost = 0;
	i = 0;
	data->ghosts->active_frame = -data->ghosts->active_frame;
	while (i < data->ghosts->count)
	{
		if (data->ghosts->active_frame > 0)
			data->ghosts->frame_left->instances[i].enabled = 1;
		else
			data->ghosts->frame_left->instances[i].enabled = 0;
		ft_set_ghost_variables(data, i);
		ft_pathfinding(data, i);
		i++;
	}
}
