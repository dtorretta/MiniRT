/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:38:45 by miguandr          #+#    #+#             */
/*   Updated: 2024/11/04 16:33:23 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	keyboard_quit(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		free_memory(data);
		exit (0);
	}
	return (0);
}

int	mouse_quit(t_data *data)
{
	free_memory(data);
	exit (0);
	return (0);
}

void	mlx_init(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		handle_error(data, 10);
	data->mlx->window = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!data->mlx->window)
		handle_error(data, 11);
	data->mlx->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	if (!data->mlx->img)
		handle_error(data, 12);
	data->mlx->address = mlx_get_data_addr(data->mlx->img, &data->mlx->bitpp,
			&data->mlx->line_lenght, &data->mlx->endian);
	if (!data->mlx->address)
		handle_error(data, 13);
}

void	ft_render(t_data *data)
{
	mlx_init(data);
	render_scene(); // TODO
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->window,
		data->mlx->img, 0, 0);
	mlx_key_hook(data->mlx->window, keyboard_quit, data);
	mlx_hook(data->mlx->window, FINISH_EVENT, 0, mouse_quit, data);
	mlx_loop(data->mlx->mlx)
}
