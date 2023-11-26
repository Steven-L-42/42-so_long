/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:14:04 by slippert          #+#    #+#             */
/*   Updated: 2023/11/11 09:36:34 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libs/libft/srcs/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}			t_direction;

typedef struct s_ghost
{
	int				count;
	int				temp_count;
	int				deceleration_ghost;
	int				calc_x;
	int				calc_y;
	int				new_x;
	int				new_y;
	int				x;
	int				y;
	int				is_pos_x;
	int				is_pos_y;
	int				active_frame;
	mlx_image_t		*frame_left;
	mlx_image_t		*frame_right;
	xpm_t			*text_left;
	xpm_t			*text_right;
}				t_ghost;

typedef struct s_pathfinding
{
	int				**map;
	int				size_x;
	int				size_y;
	int				cycled;
}				t_pathfinding;

typedef struct s_map
{
	char			**map;
	char			**copy;
	char			**coins_m;
	int				**coins_i;
	int				co_ex[2];
	int				count_exit;
	int				count_space;
	int				size_x;
	int				size_y;
}				t_map;

typedef struct s_player
{
	int				x;
	int				y;
	int				frame;
	int				count;
	int				moves;
	xpm_t			*text_frame_[6];
	mlx_image_t		*frame_[6];
}				t_player;

typedef struct s_data
{
	int				wrong_characters;
	char			*str_coins_joined;
	char			*str_coins_nbr;
	char			*str_moves_joined;
	char			*str_moves_nbr;
	t_map			*map;
	t_ghost			*ghosts;
	t_direction		dir;
	t_direction		temp_dir;
	t_player		*player;
	t_pathfinding	*path;
	mlx_t			*mlx;
	const char		*arg;
	int				coins_temp;
	int				coins;
	int				collectibles_count;
	int				deceleration;
	int				frame_dir;
	xpm_t			*text_coin;
	xpm_t			*texture_wall;
	xpm_t			*texture_exit[2];
	xpm_t			*texture_background;
	mlx_image_t		*img_exit[2];
	mlx_image_t		*game_bg;
	mlx_image_t		*game_coin;
	mlx_image_t		*game_wall;
	mlx_image_t		*img_playername;
	mlx_image_t		*img_score;
	mlx_image_t		*img_moves;
}				t_data;

void	ft_pathfinding(t_data *data, int i);
int		ft_fill_map_helper_summary(t_data *data, int *x_cmp, int (*x_y)[2]);
int		ft_fill_map(t_data *data);
int		init_summary(t_data *data);
void	set_credits(t_data *data);
void	init_loop_hooks(t_data *data);
void	ft_draw_scoreboard(void *param);
void	ft_draw_playername(void *param);
void	ft_ghost_movement(void *param);
void	ft_keypress(void *param);
void	ft_render_player(t_data *data);
void	init_map_wall_floor(t_data *data);
int		init_map_coins(t_data *data);
void	init_map_ghosts(t_data *data);
char	*ft_strdup(const char *s1);
char	*ft_strdup(const char *s1);
void	ft_freestuff(t_data *data, int sector);
int		init_load_images(t_data *data);
void	free_c(char **arr, int size);
void	free_i(int **arr, int size);
int		ft_error_handling(t_data *data, int x_cmp, int x_y[2]);
void	ft_zirkular_pathfinding(t_data *data);
int		ft_abs(int value);
void	ft_draw_movements(t_data *data);
void	free_both(char **data1, int **data2, int y);

#endif
