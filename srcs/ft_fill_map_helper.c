/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_map_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:10:18 by slippert          #+#    #+#             */
/*   Updated: 2023/11/11 10:03:52 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_fill_map_helper_two(t_data *data, int *x_cmp, int *x_y)
{
	if (*x_cmp == 0)
		*x_cmp = x_y[0];
	if ((*x_cmp != x_y[0] && x_y[1] < data->map->size_y / 32)
		|| (*x_cmp != x_y[0] + 1 && x_y[1] == data->map->size_y / 32))
		*x_cmp = -1;
}

void	ft_fill_map_helper_one(t_data *data, char *line, int *x_y)
{
	if (line[x_y[0]] == 'P')
	{
		data->player->count++;
		data->player->x = x_y[0];
		data->player->y = x_y[1];
		line[x_y[0]] = '0';
	}
	else if (line[x_y[0]] == 'C')
		data->collectibles_count++;
	else if (line[x_y[0]] == '0')
		data->map->count_space++;
	else if (line[x_y[0]] == 'E')
		data->map->count_exit++;
	else if (line[x_y[0]] != 'P' && line[x_y[0]] != 'C'
		&& line[x_y[0]] != '0' && line[x_y[0]] != 'E'
		&& line[x_y[0]] != '1' && line[x_y[0]] != '\n')
		data->wrong_characters++;
	data->map->map[x_y[1]][x_y[0]] = line[x_y[0]];
	x_y[0]++;
}

int	ft_fill_map_helper_summary(t_data *data, int *x_cmp, int (*x_y)[2])
{
	int		fd;
	char	*line;

	fd = open(data->arg, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	data->collectibles_count = 0;
	while (line)
	{
		(*x_y)[0] = 0;
		data->map->map[(*x_y)[1]]
			= ft_calloc((ft_strlen(line) + 1), sizeof(char));
		if (!data->map->map[(*x_y)[1]])
			return (free_c(data->map->map, (*x_y)[1]), 0);
		while (line[(*x_y)[0]])
			ft_fill_map_helper_one(data, line, *x_y);
		(*x_y)[1]++;
		ft_fill_map_helper_two(data, x_cmp, *x_y);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (close(fd), 1);
}
