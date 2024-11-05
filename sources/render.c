/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:38:45 by miguandr          #+#    #+#             */
/*   Updated: 2024/11/05 09:58:32 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	keyboard_exit(int keysym, t_data *data)
{
	// keysym 53 is for mac. DELETE later
	if (keysym == 0xFF1B || keysym == 53)
	{
		free_memory(data);
		exit (0);
	}
	return (0);
}

static int	mouse_exit(t_data *data)
{
	free_memory(data);
	exit (0);
	return (0);
}

static void	init_mlx(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		handle_error2(data, 0);
	data->mlx->window = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!data->mlx->window)
		handle_error2(data, 1);
	data->mlx->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	if (!data->mlx->img)
		handle_error2(data, 2);
	data->mlx->address = mlx_get_data_addr(data->mlx->img, &data->mlx->bitpp,
			&data->mlx->line_lenght, &data->mlx->endian);
	if (!data->mlx->address)
		handle_error2(data, 3);
}

void	render(t_data *data)
{
	init_mlx(data);
	//render_scene(); // TODO
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->window,
		data->mlx->img, 0, 0);
	mlx_key_hook(data->mlx->window, keyboard_exit, data);
	mlx_hook(data->mlx->window, FINISH_EVENT, 0, mouse_exit, data);
	mlx_loop(data->mlx->mlx);
}
