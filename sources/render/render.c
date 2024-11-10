/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:38:45 by miguandr          #+#    #+#             */
/*   Updated: 2024/11/11 00:04:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//closest will be the first figure the ray impact
//if there is no figure (distance = INFINITY), there will be no color (black)
//otherwhise we call the function to add the color to the pixel
static void render_pixel(int x, int y, t_data *data)
{
	t_figure    closest;
	t_figure    temp;
	t_ray       ray; //no es pointer porque quiero que se creen todas copias distintas en cada llamada
	
	closest.distance = INFINITY;
	temp.distance = INFINITY;
	//ray.direction = //TODO
	ray.origin = data->cam->origin;
	if (data->pl)
		closest = render_plane(data, ray);
	if (data->sp)
		//temp = render_sphere(data, ray) //TODO
	if (temp.distance < closest.distance)
		closest = temp;
	if (data->cy)
		//temp = render_cylinder(data, ray) //TODO
	if (temp.distance < closest.distance)
		closest = temp;
	if (closest.distance < INFINITY)
		//ft_color(x, y, data, closest); //TODO
		
}

static void render_scene(t_data *data)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	//set_camera(); //TODO
	ft_putendl_fd("Rendering scene...", 1);
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			//render_pixel(x, y, data); //In progress
			y++;
		}
		y = 0;
		x++;
	}
	ft_putendl_fd("Render done.", 1);
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
	render_scene(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->window,
		data->mlx->img, 0, 0);
	mlx_key_hook(data->mlx->window, keyboard_exit, data);
	mlx_hook(data->mlx->window, FINISH_EVENT, 0, mouse_exit, data);
	mlx_loop(data->mlx->mlx);
}
