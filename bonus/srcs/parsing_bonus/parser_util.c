/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peli <peli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:39:30 by peli              #+#    #+#             */
/*   Updated: 2025/02/28 16:30:15 by peli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	map_width(t_data *data)
{
	int		i;
	int		j;
	int		max;
	char	**map;

	i = 0;
	j = 0;
	max = 0;
	map = data->map_data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	data->map_data->width = max;
}

void	free_map_partial(char **map, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	fill_line(char *line, int width)
{
	int	i;

	i = ft_strlen(line);
	while (i < width)
	{
		line[i] = ' ';
		i++;
	}
}

char	**copy_map(t_data *data, char **map, int height)
{
	int		i;
	char	**map_copy;

	i = 0;
	map_copy = ft_calloc(height + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	while (map[i])
	{
		map_copy[i] = ft_calloc(sizeof(char), data->map_data->width + 1);
		if (!map_copy[i])
		{
			free_map_partial(map_copy, i);
			return (NULL);
		}
		ft_strlcpy(map_copy[i], map[i], data->map_data->width + 1);
		fill_line(map_copy[i], data->map_data->width);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	fill_map(t_data *data, char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line && ft_strcmp(line, "\n") == 0)
	{
		free(line);
		line = get_next_line(data->map_data->map_fd);
	}
	data->map_data->map = ft_calloc(data->map_data->height + 1, sizeof(char *));
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		data->map_data->map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(data->map_data->map_fd);
		i++;
	}
	data->map_data->map[i] = NULL;
}
