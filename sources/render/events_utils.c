/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 01:03:15 by marvin            #+#    #+#             */
/*   Updated: 2025/01/14 01:03:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void    move_camera(int keysym, t_data *data) 
{
	if (keysym == XK_w) //up
		data->cam->origin.y -= 0.1;
	if (keysym == XK_s) //down
		data->cam->origin.y += 0.1;
	if (keysym == XK_a) //right
		data->cam->origin.x += 0.1;
	if (keysym == XK_d) //left
		data->cam->origin.x -= 0.1;
}

void    move_light(int keysym, t_data *data) 
{
	if (keysym == XK_i) //up
		data->light->origin.y += 1;
	if (keysym == XK_k) //down
		data->light->origin.y -= 1;
	if (keysym == XK_j) //right
		data->light->origin.x -= 1;
	if (keysym == XK_l) //left
		data->light->origin.x += 1;
	if (keysym == XK_o)
		data->light->origin.z += 1;
	if (keysym == XK_p)
		data->light->origin.z -= 1;
}

static void    move_sp(t_sphere *spheres, double dx, double dy, double dz) 
{
	t_sphere *current = spheres;
	while (current) 
	{
		current->origin.x += dx;
		current->origin.y += dy;
		current->origin.z += dz;
		current = current->next;
	}
}

static void    move_cy(t_cylinder *cylinders, double dx, double dy, double dz) 
{
	t_cylinder *current = cylinders;
	while (current) 
	{
		current->origin.x += dx;
		current->origin.y += dy;
		current->origin.z += dz;
		current = current->next;
	}
}

void    move_objects(int keysym, t_data *data)
{
	double dx = 0, dy = 0, dz = 0;
	
	if (keysym == XK_Up || keysym == XK_t)
		dy = 1;
	else if (keysym == XK_Down || keysym == XK_g) 
		dy = -1;
	else if (keysym == XK_Right || keysym == XK_h)
		dx = 1;
	else if (keysym == XK_Left || keysym == XK_f)
		dx = -1;
	else if (keysym == XK_KP_Add)
		dz = 1;
	else if (keysym == XK_KP_Subtract)
		dz = -1;
	if (data->sp)
		move_sp(data->sp, dx, dy, dz);
	if (data->cy)
		move_cy(data->cy, dx, dy, dz);
}