/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peli <peli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:03:09 by peli              #+#    #+#             */
/*   Updated: 2025/02/28 16:20:18 by peli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_zero(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	i = -1;
	map = copy_map(data, data->map_data->map, data->map_data->height);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if ((i > 0 && map[i - 1][j] == ' ') || (map[i + 1] && map[i
						+ 1][j] == ' '))
				{
					ft_putstr_fd("Error: Map is not closed\n", 2);
					return (free_split(map), 0);
				}
			}
		}
	}
	free_split(map);
	return (1);
}

void	direction_ns(t_data *data, char direction)
{
	if (direction == 'N')
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
		data->player->plane.x = 0.66;
		data->player->plane.y = 0;
	}
	if (direction == 'S')
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
		data->player->plane.x = -0.66;
		data->player->plane.y = 0;
	}
}

void	direction_ew(t_data *data, char direction)
{
	if (direction == 'E')
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = 0.66;
	}
	if (direction == 'W')
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = -0.66;
	}
}

void	position_player(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	i = -1;
	map = data->map_data->map;
	data->player = ft_calloc(1, sizeof(t_player));
	init_player_jump(data->player);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				data->player->pos.y = i + 0.5;
				data->player->pos.x = j + 0.5;
				direction_ns(data, map[i][j]);
				direction_ew(data, map[i][j]);
				return ;
			}
		}
	}
}
