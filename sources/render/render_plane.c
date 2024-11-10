/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:59:17 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 21:59:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//t is the intersection point between the camera and the figure
//t = [-n * (Ro - c)] / [n * d]
//n = normal vector 
//Ro = ray's origin (vector)
//c = plane's origin (vector)
//d = ray's direction (vector)
static int calculate_t(t_plane *plane, t_ray ray)
{
	t_vector    temp_a;
	t_vector    temp_b;
	float       temp_c;
	float    temp_d;
	
	temp_a = ft_scale(&plane->normal, -1);
	temp_b = ft_subtraction(&ray.origin, &plane->origin);
	temp_c = ft_dot(&temp_a, &temp_b);
	temp_d = ft_dot(&plane->normal, &ray.direction);
	return((temp_c / temp_d));
}

//Ray's direction is a vector nomalized at 1. 
//Ray's distance is its direction multiplied by the distance to the closest pl
//adding the ray's origin (camera POV) to its distance gives a
//vector that goes from the origin to the closest plane.
static void closest_plane(t_figure closest, t_ray ray)
{
	t_plane *plane;
	float   temp_distance;
	t_vector ray_distance;
	
	plane = closest.plane;
	while (plane)
	{
		//closest->normal = ft_normalize (&plane->normal); //para mi la funcion a la que llama en este punto es redundante. //tambien creo que este parametro dentro de t_figure podria no existir y tomar directamente el de T_plane
		temp_distance = calculate_t (plane, ray);
		if (temp_distance > 0 && temp_distance < closest.distance)
		{
			closest.distance = temp_distance;
			closest.normal = plane->normal;
			closest.plane = plane;
			ray_distance = ft_scale(&ray.direction, closest.distance);
			closest.intersection = ft_addition(&ray.origin, &ray_distance);	
		}
		plane = plane->next;
	}
}

//all this functions basically only check if the pixel hits a plane
//if not, closest.distance remains as INFINITY and no color will be asigned
//if it intersects with a plane, t_figure closest will store the data 
//of the closest plane (in case there is more than 1)
//no light or shadow are considerer here
t_figure render_plane(t_data *data, t_ray ray)
{
	t_figure closest;

	closest.distance = INFINITY;
	closest.cylinder = NULL;
	closest.sphere = NULL;
	closest_plane(closest, ray);
	return(closest);
}
