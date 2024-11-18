/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:07:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/17 21:07:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//this function calculates sqrt[discriminant]
//the discriminant is the expression inside the square root:
//√(B^2 - C)]
//√[(l * d)^2 - (l * l - r^2)]
//if (pow_b - C) < 0 it means the rays doesn't intercept the sphere
static float calculate_distance_2(float diameter, t_quadratic *qdtc, t_vector l)
{
	float    pow_b;
	
	qdtc->radius = (diameter / 2.0f);
	pow_b = (qdtc->b * qdtc->b);
	qdtc->c = (ft_dot(&l, &l) - (qdtc->radius * qdtc->radius));
	if ((pow_b - qdtc->c) < 0)
		return (INFINITY);
	return(sqrt(pow_b - qdtc->c));
}

//t is the intersection distance between the ray and the sphere
//in a normal quadratic equation:
//t = [-B ± √(B^2 - 4AC)] / [2*A]
//where:
//A = d * d
//B = 2 * L * d 
//C = L * L - r^2
//after some simplifications:
//t = {-(L*d) ± √[(L*d)^2 - (L^2 - r^2)]}
//L = Sphere's center - ray's origin (vector)
//d = ray's direction (vector)
//r = sphere's ratius
//± means there are 2 possible interesctions. we will return the closets.
//if temp_d is NOT >= 0, there is no interesection between the ray and the sp
static float calculate_distance(t_sphere *sphere, t_ray ray)
{
	t_quadratic    *qdtc;
	t_vector    l;
	
	l = ft_subtraction(&sphere->origin, &ray.origin);
	qdtc->b = ft_dot(&l, &ray.direction);
	qdtc->square = calculate_distance_2(sphere->diameter, qdtc, l);
	if(qdtc->square < 0 || qdtc->square == INFINITY)
		return (INFINITY);
	qdtc->dist1 = (-qdtc->b + qdtc->square);
	qdtc->dist2 = (-qdtc->b - qdtc->square);
	if(qdtc->dist1 >= 0 && (qdtc->dist1 < qdtc->dist2 || qdtc->dist2 <= 0))
		return(qdtc->dist1);
	else if (qdtc->dist2 >= 0)
		return(qdtc->dist2);
	else
		return (INFINITY);
}

//Ray's direction is a vector nomalized at 1. 
//Ray's distance is its direction multiplied by the distance to the closest sp
//adding the ray's origin (camera POV) to its distance gives a
//vector that goes from the origin to the closest sphere.
static void closest_sphere(t_figure *closest, t_ray ray)
{
	t_sphere *sphere;
	float   temp_distance;
	t_vector ray_distance;
	
	sphere = closest->sphere;
	while (sphere)
	{
		temp_distance = calculate_distance (sphere, ray);
		if (temp_distance >= 0 && temp_distance < closest->distance)
		{
			closest->distance = temp_distance;
			closest->sphere = sphere;
			ray_distance = ft_scale(&ray.direction, closest->distance);
			closest->intersection = ft_addition(&ray.origin, &ray_distance);	
			closest->normal = ft_subtraction(&closest->intersection, &sphere->origin);
			closest->normal = ft_normalize(&closest->normal);
		}
		sphere = sphere->next;
	}
}

//all this functions basically only check if the pixel hits a sphere
//if not, closest.distance remains as INFINITY and no color will be asigned
//if it intersects with a sphere, t_figure closest will store the data 
//of the closest sphere (in case there is more than 1)
//no light or shadow are considerer here
t_figure render_sphere(t_data *data, t_ray ray)
{
	t_figure closest;

	closest.distance = INFINITY;
	closest.cylinder = NULL;
	closest.plane = NULL;
	closest.sphere = data->sp;
	closest_sphere(&closest, ray);
	return(closest);
}

