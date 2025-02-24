/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:12:44 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/02/16 17:01:33 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	free(data->mlx_data);
	free(data->player);
	free(data->texture);
	free(data->map_data->map);
	free(data->map_data);
	free(data);
}

void	exit_program(t_data *data, int status)
{
	if (data->mlx_data->mlx)
		mlx_terminate(data->mlx_data->mlx);
	mlx_delete_texture(data->texture->north);
	mlx_delete_texture(data->texture->south);
	mlx_delete_texture(data->texture->east);
	mlx_delete_texture(data->texture->west);
	mlx_delete_texture(data->texture->floor);
	mlx_delete_texture(data->texture->ceiling);
	free_data(data);
	exit(status);
}

// void	draw_player(t_data *data, t_vec2i pos, int size)
// {
// 	t_vec2i	center;
// 	t_vec2i	end;
//
// 	center.x = pos.x + size / 2;
// 	center.y = pos.y + size / 2;
// 	end.x = center.x + cos(deg_to_rad(data->player->rotation)) * size / 2;
// 	end.y = center.y + sin(deg_to_rad(data->player->rotation)) * size / 2;
// 	draw_line(data, center, end, RED);
// 	draw_circle(data, center, size / 2, GREEN);
// }

// void render_minimap(t_data *data)
// {
// 	(void)data;
// }

void	ft_swap_pointers(void **ptr1, void **ptr2)
{
	void	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

void	render_all(void *vdata)
{
	t_data	*data;

	data = (t_data *)vdata;
	handle_movement(data);
	handle_strafe(data);
	handle_rotation(data);
	handle_camera_tilt(data);
	if (!data->mlx_data->img_buffer)
		data->mlx_data->img_buffer = mlx_new_image(data->mlx_data->mlx,
				data->mlx_data->mlx->width, data->mlx_data->mlx->height);
	render_raycast(data);
	ft_swap_pointers((void **)&data->mlx_data->img,
		(void **)&data->mlx_data->img_buffer);
	mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->img, 0, 0);
	if (data->mlx_data->img_buffer)
	{
		mlx_delete_image(data->mlx_data->mlx, data->mlx_data->img_buffer);
		data->mlx_data->img_buffer = NULL;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	(void)av;
	if (ac < 2)
	{
		ft_putstr_fd("Error: No map file provided\n", 2);
		return (1);
	}
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data) == -1)
		exit_program(data, 1);
	// render_minimap(data);
	mlx_key_hook(data->mlx_data->mlx, key_callback, data);
	mlx_loop_hook(data->mlx_data->mlx, render_all, data);
	mlx_loop(data->mlx_data->mlx);
	free_data(data);
}
