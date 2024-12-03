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
	dist3 = cap_distance(cylinder, ray, qdtc, closest);
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

// float	ft_hit_cap(t_cylinder *cylinder, t_ray ray, t_vector cap_center)
// {
// 	float		t;
// 	t_vector	oc;
// 	t_vector	hitpoint;
// 	t_vector	scaled_ray;
// 	float		distance;

// 	oc = ft_subtraction(&cap_center, &ray.origin);
// 	t = ft_dot(&oc, &cylinder->normal) / ft_dot(&ray.direction,
// 			&cylinder->normal);
// 	scaled_ray = ft_scale(&ray.direction, t);
// 	hitpoint = ft_addition(&ray.origin, &scaled_ray);
// 	scaled_ray = ft_subtraction(&hitpoint, &cap_center);
// 	distance = ft_lenght(&scaled_ray);
// 	if (distance <= cylinder->diameter / 2.0f)
// 		return (t);
// 	return (INFINITY);
// }

// // calculate the intersection with the cylinder caps:
// // calculate the center of the bottom and top caps
// // send both caps to the hit_cap function
// // if the ray intersects either of the caps, return the hit distance
// float	ft_inter_cap(t_cylinder *cylinder, t_ray ray, float comp_t, t_figure *hit)
// {
// 	t_vector	scaled_direction;
// 	t_vector	cap_center_bottom;
// 	t_vector	cap_center_top;
// 	float		closest_t;
// 	float		t;

// 	closest_t = INFINITY;
// 	scaled_direction = ft_scale(&cylinder->normal,
// 			(cylinder->height / 2.0f));
// 	cap_center_bottom = ft_subtraction(&cylinder->origin, &scaled_direction);
// 	cap_center_top = ft_addition(&cylinder->origin, &scaled_direction);
// 	t = ft_hit_cap(cylinder, ray, cap_center_bottom);
// 	if (t != INFINITY)
// 		closest_t = t;
// 	t = ft_hit_cap(cylinder, ray, cap_center_top);
// 	if (t != INFINITY && t < closest_t)
// 		closest_t = t;
// 	if (closest_t < comp_t)
// 		hit->cylinder_cap = 1;
// 	return (closest_t);
// }

// // calculate the intersection with infinite cylinder
// // check if the hit is within the cylinder height
// int	ft_check_height(t_cylinder *cylinder, t_ray ray, float t)
// {
// 	t_vector	hitpoint;
// 	float		projected_height;
// 	t_vector	scaled_direction;
// 	t_vector	subtracted;

// 	scaled_direction = ft_scale(&ray.direction, t);
// 	hitpoint = ft_addition(&ray.origin, &scaled_direction);
// 	subtracted = ft_subtraction(&hitpoint, &cylinder->origin);
// 	projected_height = ft_dot(&subtracted, &cylinder->normal);
// 	if (projected_height >= -cylinder->height / 2.0f && projected_height
// 		<= cylinder->height / 2.0f)
// 		return (1);
// 	return (0);
// }

// // calculate the normal vector of the hit point
// void	ft_calculate_normal_c(t_cylinder *cylinder, t_figure *hit)
// {
// 	t_vector	projection;
// 	t_vector	hit_to_origin;

// 	if (hit->cylinder_cap)
// 	{
// 		hit->normal = cylinder->normal;
// 		return ;
// 	}
// 	hit_to_origin = ft_subtraction(&hit->intersection, &cylinder->origin);
// 	projection = ft_scale(&cylinder->normal, ft_dot(&hit_to_origin,
// 				&cylinder->normal));
// 	hit->normal = ft_subtraction(&hit_to_origin, &projection);
// 	hit->normal = ft_normalize(&hit->normal);
// }

// float	*ft_discriminant_c(t_cylinder *cylinder, t_ray ray)
// {
// 	t_vector	perp_dir;
// 	t_vector	perp_oc;
// 	float		*calc;

// 	calc = (float *)malloc(sizeof(float) * 4);
// 	if (!calc)
// 		return (NULL);
// 	perp_dir = ft_perpendicular(&ray.direction, &cylinder->normal);
// 	perp_oc = ft_subtraction(&ray.origin, &cylinder->origin);
// 	perp_oc = ft_perpendicular(&perp_oc, &cylinder->normal);
// 	calc[0] = ft_dot(&perp_dir, &perp_dir);
// 	calc[1] = 2.0 * ft_dot(&perp_dir, &perp_oc);
// 	calc[2] = ft_dot(&perp_oc, &perp_oc) - (cylinder->diameter / 2.0f)
// 		* (cylinder->diameter / 2.0f);
// 	calc[3] = calc[1] * calc[1] - 4.0f * calc[0] * calc[2];
// 	return (calc);
// }

// // calc = {a, b, c, discriminant}
// float	ft_inter_c(t_cylinder *cylinder, t_ray ray, t_figure *hit)
// {
// 	float		*calc;
// 	float		t1;
// 	float		t2;
// 	float		t3;
// 	float		closest_t;

// 	closest_t = INFINITY;
// 	calc = ft_discriminant_c(cylinder, ray);
// 	if (calc[3] >= 0)
// 	{
// 		t1 = (-calc[1] - sqrt(calc[3])) / (2.0f * calc[0]);
// 		t2 = (-calc[1] + sqrt(calc[3])) / (2.0f * calc[0]);
// 		if (t1 > 0 && ft_check_height(cylinder, ray, t1))
// 			closest_t = t1;
// 		if (t2 > 0 && ft_check_height(cylinder, ray, t2) && t2 < closest_t)
// 			closest_t = t2;
// 	}
// 	t3 = ft_inter_cap(cylinder, ray, closest_t, hit);
// 	if (t3 < closest_t)
// 		closest_t = t3;
// 	free(calc);
// 	return (closest_t);
// }

// void	ft_find_closest_c(t_data *data, t_ray ray, t_figure *hit, float t)
// {
// 	t_cylinder	*cylinder;
// 	float		hit_distance;
// 	t_vector	scaled_direction;

// 	cylinder = data->cy;
// 	while (cylinder)
// 	{
// 		cylinder->normal = ft_normalize(&cylinder->normal);
// 		hit_distance = ft_inter_c(cylinder, ray, hit);
// 		if (hit_distance < t)
// 		{
// 			t = hit_distance;
// 			hit->cylinder = cylinder;
// 			hit->distance = hit_distance;
// 			scaled_direction = ft_scale(&ray.direction, t);
// 			hit->intersection = ft_addition(&ray.origin, &scaled_direction);
// 			ft_calculate_normal_c(cylinder, hit);
// 			hit->sphere = NULL;
// 			hit->plane = NULL;
// 		}
// 		cylinder = cylinder->next;
// 	}
// }

// // draw sphere
// t_figure	render_cylinder(t_data *data, t_ray ray)
// {
// 	float		closest_t;
// 	t_figure		hit_result;

// 	closest_t = INFINITY;
// 	hit_result.distance = INFINITY;
// 	hit_result.sphere = NULL;
// 	hit_result.plane = NULL;
// 	hit_result.cylinder_cap = 0;
// 	ft_find_closest_c(data, ray, &hit_result, closest_t);
// 	return (hit_result);
// }