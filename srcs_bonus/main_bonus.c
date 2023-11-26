/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:16:44 by slippert          #+#    #+#             */
/*   Updated: 2023/11/02 16:55:37 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	ft_check_file_extension(t_data *data)
{
	int		i;
	int		length;
	char	extension[4];

	extension[0] = '.';
	extension[1] = 'b';
	extension[2] = 'e';
	extension[3] = 'r';
	i = 0;
	length = ft_strlen((char *)data->arg) - 4;
	while (data->arg[length])
	{
		if (data->arg[length++] != extension[i++])
			return (0);
	}
	return (1);
}

int	ft_alloc_structs(t_data *data)
{
	data->map = (t_map *)malloc(sizeof(t_map));
	if (!data->map)
		return (0);
	data->path = (t_pathfinding *)malloc(sizeof(t_pathfinding));
	if (!data->path)
		return (free(data->map), 0);
	data->ghosts = (t_ghost *)malloc(sizeof(t_ghost));
	if (!data->ghosts)
		return (free(data->map), free(data->path), 0);
	data->player = (t_player *)malloc(sizeof(t_player));
	if (!data->player)
		return (free(data->map), free(data->path),
			free(data->ghosts), 0);
	return (1);
}

int	ft_do_first_action(t_data *data)
{
	if (!ft_check_file_extension(data))
		return (ft_printf
			("Error\nFile extension needs to end with (.ber)!\n"), 0);
	if (!ft_fill_map(data))
		return (ft_printf
			("Error\nCreation of main map were unsuccessful!\n"), 0);
	if (!init_summary(data))
		return (ft_printf
			("Error\nInitialization of images were unsuccessful!\n"), 0);
	return (1);
}

int	main(int argc, const char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!ft_alloc_structs(data))
		return (1);
	data->arg = argv[1];
	if (!ft_do_first_action(data))
		return (ft_freestuff(data, 0), 0);
	set_credits(data);
	init_loop_hooks(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_freestuff(data, 1);
	return (0);
}
//system("leaks so_long");
