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
//(l * d)^2 - (l * l - r^2)
//if (temp_b - temp_c) < 0 it means the rays doesn't intercept the sphere
static float	calculate_distance_2(float diameter, float temp_a, t_vector l)
{
	float	radius;
	float	temp_b;
	float	temp_c;

	radius = (diameter / 2.0f);
	temp_b = (temp_a * temp_a); //(l * d)^2
	temp_c = (ft_dot(&l, &l) - (radius * radius)); //(l * l - r^2)
	if ((temp_b - temp_c) < 0)
		return (INFINITY);
	return (sqrt(temp_b - temp_c)); //sqrt[ (l * d)^2 - (l * l - r^2) ]
}

//t is the intersection distance between the ray and the sphere
//in a normal quadratic equation:
//t = [-B ± √(B^2 - 4AC)] / [2*A]
//where:
//A = d * d
//B = 2 * L * d
//C = l * L - r^2
//(we can omit the '2*' in B and in the denominator)
//t = {-(L*d) ± √[(L*d)^2 - (L^2 - r^2)]} / {d*d}
//L = Sphere's center - ray's origin (vector)
//d = ray's direction (vector)
//r = sphere's ratius
//± means there are 2 possible interesctions. we will return the closets.
//if temp_d is NOT >= 0, there is no interesection between the ray and the sp
static float	calculate_distance(t_sphere *sphere, t_ray ray)
{
	t_vector	l;
	float		temp_a;
	float		temp_d;
	float		distance_a;
	float		distance_b;

	l = ft_subtraction(&sphere->origin, &ray.origin);
	temp_a = ft_dot(&l, &ray.direction); //(l * d)
	temp_d = calculate_distance_2(sphere->diameter, temp_a, l);
	if (temp_d < 0 || temp_d == INFINITY)
		return (INFINITY);
	distance_a = ((-temp_a + temp_d) / ft_dot(&ray.direction, &ray.direction));
	distance_b = ((-temp_a - temp_d) / ft_dot(&ray.direction, &ray.direction));
	if (distance_a >= 0 && (distance_a < distance_b || distance_b <= 0))
		return (distance_a);
	else if (distance_b >= 0)
		return (distance_b);
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
		//closest->normal = ft_normalize (&plane->normal); //para mi la funcion a la que llama en este punto es redundante.
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
