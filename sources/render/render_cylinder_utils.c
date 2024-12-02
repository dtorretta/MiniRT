/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:56:15 by marvin            #+#    #+#             */
/*   Updated: 2024/11/24 22:56:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//The ray intercepts the cap when (V's magnitude ≤ radius)
//V = P − C
//V's magnitude = v's lenght
//where:
//P = intersection's point
//C = cap's origin
//**calculate P**
//P = O + t * D
//where:
//O = Ray's origin
//t = intersection
//D = Ray's direction
//**calculate t**
//t = [N * (C - O)] / N * D
//where:
//N = normalized vector;
static float   cap_t(t_cylinder *cy, t_ray ray, t_quadratic *q, t_vector cap_center)
{   
	t_vector temp;
	t_vector point;
	t_vector v;
	float t;
	
	temp = ft_subtraction(&cap_center, &ray.origin); //(C - O) //ok
	t = ft_dot(&cy->normal, &temp) / ft_dot(&cy->normal, &ray.direction); //ok
	if(t >= 0) //>=??
	{
		temp = ft_scale(&ray.direction, t); //ok
		point = ft_addition(&ray.origin, &temp); //ok
		v = ft_subtraction(&point, &cap_center); //ok
		if (ft_lenght(&v) <= q->radius)
			return(t);
	}
	return(INFINITY);
}

float   cap_distance(t_cylinder *cylinder, t_ray ray, t_quadratic *qdtc)
{
	float dist_sup;
	float dist_inf;
	t_vector cap_center_sup;
	t_vector cap_center_inf;
	t_vector scaled_direction;
	
	scaled_direction = ft_scale(&cylinder->normal, cylinder->height / 2.0f); //ok
	cap_center_sup = ft_addition(&cylinder->origin, &scaled_direction); //ok
	cap_center_inf = ft_subtraction(&cylinder->origin, &scaled_direction); //ok
	dist_sup = cap_t(cylinder, ray, qdtc, cap_center_sup);
	dist_inf = cap_t(cylinder, ray, qdtc, cap_center_inf);	
	//if (dist_sup < dist_inf && (dist_sup > 0 && dist_inf > 0))
	if (dist_sup < dist_inf && dist_sup != INFINITY)
	{	
		cylinder->cy_cap = true;
		return(dist_sup);
	}
	//else if (dist_inf > 0 && dist_inf != INFINITY)
	else if (dist_inf != INFINITY)
	{	
		cylinder->cy_cap = true;
		return(dist_inf);
	}
	return(INFINITY);
}

//height_projection = V * N
//V = P - C
//N = normalized vector;
//P = intersection's point
//C = Cylinders'origin
//**calculate P**
//P = O + t * D
//where:
//O = Ray's origin
//t = intersection (dist1 or dist2)
//D = Ray's direction
//as the cylinder->origin is the center of it, 
//its height is distributed up and down symmetrically from that point.
int check_height(t_cylinder *cy, t_ray ray, float dist)
{
	t_vector point;
	t_vector v;
	t_vector scaled_direction;
	float height_projection;
	
	scaled_direction = ft_scale(&ray.direction, dist);
	point = ft_addition(&ray.origin, &scaled_direction);
	v = ft_subtraction(&point, &cy->origin);
	height_projection = ft_dot(&v, &cy->normal);
	if (height_projection >= -cy->height / 2.0f && height_projection <= cy->height / 2.0f)
		return(1);
	return(0);
}
