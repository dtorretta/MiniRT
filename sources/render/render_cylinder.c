/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:04:56 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 01:04:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//this function calculates sqrt[discriminant]
//the discriminant is the expression inside the square root:
//√(B^2 - C)]
//√[(Rp * Lp)^2 - (Lp^2 - r^2)]
//if (pow_b - C) < 0 it means the rays doesn't intercept the cylinder
static float calculate_distance_2(float diameter, t_vector perp_l, t_quadratic *qdtc)
{
	float    pow_b;

	qdtc->radius = (diameter / 2.0f);
	pow_b = (qdtc->b * qdtc->b);
	qdtc->c = ft_dot(&perp_l, &perp_l) - (qdtc->radius * qdtc->radius);
	if ((pow_b - qdtc->c) < 0)
		return (INFINITY);
	return(sqrt(pow_b - qdtc->c));
}

//t is the intersection distance between the ray and the cylinder
//in a normal quadratic equation:
//t = [-B ± √(B^2 - 4AC)] / [2*A]
//where:
//A = Rp^2
//B = 2 * Rp * Lp
//C = Lp^2 − r^2
//after some simplifications:
//t = {-(Rp * Lp) ± √[(Rp * Lp)^2 - (Lp^2 − r^2)]}
//where:
//Lp = perperdicular component of L
//L = ray's origin - cylinder's center (vector)
//Rp = perperdicular component of ray's origin
//r = cylinder's ratius
//± means there are 2 possible interesctions. we will return the closets.
//if temp_d is NOT >= 0, there is no interesection between the ray and the cy
static float calculate_distance(t_cylinder *cylinder, t_ray ray)
{
	t_quadratic    *qdtc;
	t_vector       perp_ray;
	t_vector       perp_l;

	perp_ray = ft_perpendicular(&ray.direction, &cylinder->normal);
	perp_l = ft_subtraction(&ray.origin, &cylinder->origin);
	perp_l = ft_perpendicular(&perp_l, &cylinder->normal);
	qdtc->b = ft_dot(&perp_ray, &perp_l);
	qdtc->square = calculate_distance_2(cylinder->diameter, perp_l, qdtc);
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
//Ray's distance is its direction multiplied by the distance to the closest pl
//adding the ray's origin (camera POV) to its distance gives a
//vector that goes from the origin to the closest cylinder.
static void	closest_cylinder(t_figure *closest, t_ray ray)
{
	t_cylinder	*cylinder;
	float		temp_distance;
	t_vector	ray_distance;

	cylinder = closest->cylinder;
	while (cylinder)
	{
		temp_distance = calculate_distance (cylinder, ray);
		if (temp_distance >= 0 && temp_distance < closest->distance)
		{
			closest->distance = temp_distance;
			closest->normal = cylinder->normal;
			closest->cylinder = cylinder;
			ray_distance = ft_scale(&ray.direction, closest->distance);
			closest->intersection = ft_addition(&ray.origin, &ray_distance);
		}
		cylinder = cylinder->next;
	}
}

//all this functions basically only check if the pixel hits a cylinder
//if not, closest.distance remains as INFINITY and no color will be asigned
//if it intersects with a cylinder, t_figure closest will store the data
//of the closest cylinder (in case there is more than 1)
//no light or shadow are considerer here
t_figure	render_cylinder(t_data *data, t_ray ray)
{
	t_figure	closest;

	closest.distance = INFINITY;
	closest.plane = NULL;
	closest.sphere = NULL;
	closest.cylinder = data->cy;
	closest_cylinder(&closest, ray);
	return (closest);
}
