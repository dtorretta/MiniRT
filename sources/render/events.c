/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:24:06 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 21:24:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"






void    resize_objects(int keysym, t_data *data)
{
	t_sphere *current_sp;
	t_cylinder *current_cy;
	double size;
	
	size = 1;
	if (keysym == XK_2)
		size = -1;
	if (data->sp)
	{
		current_sp = data->sp;
		while (current_sp) 
		{
			current_sp->diameter += size;
			current_sp = current_sp->next;
		}
	}
	if (data->cy)
	{
		current_cy = data->cy;
		while (current_cy) 
		{
			current_cy->diameter += size;
			current_cy->height += size;
			current_cy = current_cy->next;
		}
	}
}

int key_handle(int keysym, t_data *data)
{
	if (keysym == XK_m)
		print_menu();
		
	//translation of light
	if (keysym == XK_i || keysym == XK_k || keysym == XK_j || keysym == XK_l || keysym == XK_o || keysym == XK_p)
		move_light(keysym, data);
		
	//translation of camera
	if (keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
		move_camera(keysym, data);
	
	//translation of objetcs
	if (keysym == XK_Up || keysym == XK_Down || keysym == XK_Right || keysym == XK_Left || XK_KP_Add || XK_KP_Subtract)
		move_objects(keysym, data);

	//rotation
	if (keysym == XK_z || keysym == XK_x || keysym == XK_c || keysym == XK_v)
		rotate_objects(keysym, data);
	
	//resize
	if (keysym == XK_1 || keysym == XK_2)
		resize_objects(keysym, data);
	
	render_scene(data);
	return (0); //necesario?
}

int	keyboard_exit(int keysym, t_data *data)
{
	// keysym 53 is for mac. DELETE later
	if (keysym == 0xFF1B || keysym == 53)
	{
		free_memory(data);
		exit (0);
	}
	return (0);
}

int	mouse_exit(t_data *data)
{
	free_memory(data);
	exit (0);
	return (0);
}
