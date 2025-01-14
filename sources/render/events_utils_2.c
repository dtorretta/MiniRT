/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 01:06:02 by marvin            #+#    #+#             */
/*   Updated: 2025/01/14 01:06:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void    rotate_pl(t_plane *planes, double angle) 
{
	t_plane *current = planes;
	while (current) 
	{
		double angle_radians = angle * M_PI / 180.0; 
		double original_x = current->normal.x;
		double original_y = current->normal.y;
		current->normal.x = original_x * cos(angle_radians) - original_y * sin(angle_radians);
		current->normal.y = original_x * sin(angle_radians) + current->normal.y * cos(angle_radians);
		current = current->next;
	}	
}

static void    rotate_cy(t_cylinder *cy, double angle) 
{
	t_cylinder *current = cy;
	while (current) 
	{
		double angle_radians = angle * M_PI / 180.0; 
		double original_x = current->normal.x;
		double original_y = current->normal.y;
		current->normal.x = original_x * cos(angle_radians) - original_y * sin(angle_radians);
		current->normal.y = original_x * sin(angle_radians) + original_y * cos(angle_radians);
		current = current->next;
	}	
}

void    rotate_objects(int keysym, t_data *data)
{
	double angle;
	
	angle = 0;
	if (keysym == XK_z || keysym == XK_c)
		angle = 15.0;
	if (keysym == XK_x || keysym == XK_v) 
		angle = -15.0;
		
	if(keysym == XK_z || keysym == XK_x)
	{
		if (data->cy)
		rotate_cy(data->cy, angle);
	}
	if(keysym == XK_c || keysym == XK_v)
	{
		if (data->pl)
			rotate_pl(data->pl, angle);
	}
}
