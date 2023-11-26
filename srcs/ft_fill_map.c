/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:10:18 by slippert          #+#    #+#             */
/*   Updated: 2023/11/11 09:50:06 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	ft_create_pathfinding_map(t_data *data)
{
	int	y;

	y = 0;
	data->path->map
		= ft_calloc(data->map->size_y + 1, sizeof(int *));
	if (!data->path->map)
		return (0);
	y = 0;
	while (y < data->map->size_y)
	{
		data->path->map[y]
			= ft_calloc(data->map->size_x + 1, sizeof(int));
		if (!data->path->map[y])
			return (free_i(data->path->map, y), 0);
		y++;
	}
	return (1);
}

static int	ft_create_map(t_data *data)
{
	char	*anti_leak;
	int		fd;
	int		y;

	y = 0;
	fd = open(data->arg, O_RDONLY);
	if (fd == -1 || read(fd, 0, 0) < 0)
		return (ft_printf
			("Error\nFile not readable or does not exist!\n"), 0);
	anti_leak = get_next_line(fd);
	while (anti_leak)
	{
		y++;
		free(anti_leak);
		anti_leak = get_next_line(fd);
	}
	if (anti_leak)
		free(anti_leak);
	close(fd);
	data->map->size_y = y * 32;
	data->map->map = ft_calloc(data->map->size_y + 1, sizeof(char *));
	if (!data->map->map)
		return (0);
	return (1);
}

static char	**copy_map(char **mat)
{
	int		size;
	char	**copy;
	char	*tmp;
	int		i;

	size = 0;
	while (mat[size])
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	copy[size] = NULL;
	i = -1;
	while (++i < size)
	{
		tmp = ft_strdup(mat[i]);
		if (!tmp)
			free_c(copy, i);
		copy[i] = tmp;
	}
	return (copy);
}

static void	is_playable(t_data *data, int x, int y, int *co_ex)
{
	if (data->player->count != 1)
		return ;
	if (data->map->copy[y][x] == 'C')
		(co_ex[0])--;
	if (data->map->copy[y][x] == 'E')
		(co_ex[1])--;
	else
	{
		data->map->copy[y][x] = '1';
		if (data->map->copy[y][x + 1] != '1')
			is_playable(data, x + 1, y, co_ex);
		if (data->map->copy[y + 1][x] != '1')
			is_playable(data, x, y + 1, co_ex);
		if (data->map->copy[y][x - 1] != '1')
			is_playable(data, x - 1, y, co_ex);
		if (data->map->copy[y - 1][x] != '1')
			is_playable(data, x, y - 1, co_ex);
	}
}

int	ft_fill_map(t_data *data)
{
	int		x_cmp;
	int		x_y[2];

	if (!ft_create_map(data))
		return (0);
	data->player->count = 0;
	data->map->count_space = 0;
	data->map->count_exit = 0;
	data->wrong_characters = 0;
	x_y[1] = 0;
	x_cmp = 0;
	ft_fill_map_helper_summary(data, &x_cmp, &x_y);
	data->map->size_x = x_y[0] * 32;
	data->map->map[x_y[1]] = NULL;
	data->map->co_ex[0] = data->collectibles_count;
	data->map->co_ex[1] = data->map->count_exit;
	data->map->copy = copy_map(data->map->map);
	is_playable(data, data->player->x, data->player->y, data->map->co_ex);
	if (!ft_error_handling(data, x_cmp, &x_y[0]))
		return (0);
	if (!ft_create_pathfinding_map(data))
		return (0);
	return (1);
}
