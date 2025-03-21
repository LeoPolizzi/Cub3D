/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:12:44 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/03/12 12:24:46 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	free(data->mlx_data);
	free(data->player);
	if (data->texture->north)
		mlx_delete_texture(data->texture->north);
	if (data->texture->south)
		mlx_delete_texture(data->texture->south);
	if (data->texture->east)
		mlx_delete_texture(data->texture->east);
	if (data->texture->west)
		mlx_delete_texture(data->texture->west);
	if (data->texture->floor)
		mlx_delete_texture(data->texture->floor);
	if (data->texture->ceiling)
		mlx_delete_texture(data->texture->ceiling);
	while (++i < NUM_FRAMES && data->texture->doors[i])
		mlx_delete_texture(data->texture->doors[i]);
	free(data->texture);
	close(data->map_data->map_fd);
	free_split(data->map_data->map);
	free(data->map_data->map_1d);
	free(data->map_data);
	free(data);
}

void	exit_program(t_data *data, int status)
{
	if (data && data->mlx_data && data->mlx_data->mlx)
		mlx_terminate(data->mlx_data->mlx);
	free_data(data);
	exit(status);
}

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
	handle_jump(data, data->mlx_data->mlx->delta_time);
	render_raycast(data);
	render_minimap(data);
	ft_swap_pointers((void **)&data->mlx_data->img->pixels,
		(void **)&data->mlx_data->img_buffer->pixels);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 2)
	{
		ft_putstr_fd("Error: No map file provided\n", 2);
		return (1);
	}
	data = ft_calloc(1, sizeof(t_data));
	mlx_set_setting(MLX_FULLSCREEN, true);
	if (!data || !parsing(data, av[1]) || !init_mlx(data))
		exit_program(data, 1);
	mlx_set_cursor_mode(data->mlx_data->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(data->mlx_data->mlx, data->mlx_data->mlx->width / 2,
		data->mlx_data->mlx->height / 2);
	mlx_image_to_window(data->mlx_data->mlx, data->mlx_data->img, 0, 0);
	mlx_key_hook(data->mlx_data->mlx, key_callback, data);
	mlx_cursor_hook(data->mlx_data->mlx, handle_cursor, data);
	mlx_loop_hook(data->mlx_data->mlx, render_all, data);
	mlx_loop(data->mlx_data->mlx);
	free_data(data);
}
