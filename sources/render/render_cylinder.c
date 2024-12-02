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

static float calculate_distance_2(t_cylinder *cylinder, t_ray ray, t_quadratic *qdtc)
{
	float           dist3;
	float           closest;
	
	qdtc->dist1 = (-qdtc->b + qdtc->square) / (2.0f * qdtc->a);
	qdtc->dist2 = (-qdtc->b - qdtc->square) / (2.0f * qdtc->a);
	closest = INFINITY;
	if(qdtc->dist1 >= 0 && check_height(cylinder, ray, qdtc->dist1))
		closest = qdtc->dist1;
	if (qdtc->dist2 >= 0 && check_height(cylinder, ray, qdtc->dist2) && qdtc->dist2 < closest)
		closest = qdtc->dist2;
	dist3 = cap_distance(cylinder, ray, qdtc);
	if (dist3 < closest)
		closest = dist3;
	return (closest);
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
//Rp = perperdicular component of ray
//r = cylinder's ratius
//± means there are 2 possible interesctions. we will return the closets.
//if temp_d is NOT >= 0, there is no interesection between the ray and the cy
static float calculate_distance(t_cylinder *cylinder, t_ray ray)
{
	t_vector       perp_ray;
	t_vector       perp_l;
	t_quadratic    qdtc;
	float    pow_b;

	qdtc = cylinder->qdtc;
	perp_ray = ft_perpendicular(&ray.direction, &cylinder->normal);
	perp_l = ft_subtraction(&ray.origin, &cylinder->origin);
	perp_l = ft_perpendicular(&perp_l, &cylinder->normal);
	qdtc.a = ft_dot(&perp_ray, &perp_ray);
	qdtc.b = 2.0 * ft_dot(&perp_ray, &perp_l);
	qdtc.radius = (cylinder->diameter / 2.0f);
	pow_b = (qdtc.b * qdtc.b);
	qdtc.c = ft_dot(&perp_l, &perp_l) - (qdtc.radius * qdtc.radius);
	if ((pow_b - 4.0f * qdtc.a * qdtc.c) < 0)
		return (INFINITY);
	qdtc.square = (sqrt(pow_b - 4.0f * qdtc.a * qdtc.c));
	return (calculate_distance_2(cylinder, ray, &qdtc));
}

//calculate the normal vector of the intersection
//if the intersection is on the cylinder's cap, it will bethe cylinder->normal
//This is because the caps are flat and parallel to the cylinder's axis. 
//Therefore, any point on the cap has the same normal as the axis.
//if that does not happen, t = interection to origin − projection
//where:
//intersection: is the displacement from the cylinder's origin to 
//its point of intersection
//projection: (intersection * N) * N
static t_vector	calculate_normal(t_cylinder *cylinder, t_figure *closest)
{
	t_vector	projection;
	t_vector	intersection;
	t_vector    t;

	if (cylinder->cy_cap == true)
		return (cylinder->normal);	
	intersection  = ft_subtraction(&closest->intersection, &cylinder->origin);
	projection = ft_scale(&cylinder->normal, ft_dot(&intersection , &cylinder->normal));
	t = ft_subtraction(&intersection , &projection);
	return (ft_normalize(&t));
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
		cylinder->cy_cap = false;
		temp_distance = calculate_distance (cylinder, ray);
		if (temp_distance >= 0 && temp_distance < closest->distance)
		{
			closest->distance = temp_distance;
			closest->cylinder = cylinder;
			ray_distance = ft_scale(&ray.direction, closest->distance);
			closest->intersection = ft_addition(&ray.origin, &ray_distance);
			closest->normal = calculate_normal(cylinder, closest);
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
