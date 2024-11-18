/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:58:48 by miguandr          #+#    #+#             */
/*   Updated: 2024/11/18 20:55:40 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Traces a shadow ray to check for intersections with objects in the scene.
 * @data: Pointer to the scene data containing the list of objects.
 * @shadow_ray: Pointer to the shadow ray being traced.
 * @light_distance: Distance from the surface point to the light source.
 *
 * Iterates through all objects in the scene to find the closest intersection
 * point along the shadow ray. If an object is closer than the light source
 * and beyond a minimal threshold (0.001f), the function returns 1 (in shadow).
 * Returns 0 if no objects block the light source.
 */
static int	trace_shadow_ray(t_data *data,
	t_ray *shadow_ray, float light_distance)
{
	t_figure	nearest_intersection;
	t_figure	current_intersection;

	nearest_intersection.distance = INFINITY;
	if (data->sp)
	{
		current_intersection = render_sphere(data, *shadow_ray);
		if (current_intersection.distance < nearest_intersection.distance)
			nearest_intersection = current_intersection;
	}
	if (data->pl)
	{
		current_intersection = render_plane(data, *shadow_ray);
		if (current_intersection.distance < nearest_intersection.distance)
			nearest_intersection = current_intersection;
	}
	if (data->cy)
	{
		current_intersection = render_cylinder(data, *shadow_ray);
		if (current_intersection.distance < nearest_intersection.distance)
			nearest_intersection = current_intersection;
	}
	return (nearest_intersection.distance > 0.001f
		&& nearest_intersection.distance < light_distance);
}

/**
 * Checks if a point on a surface is in shadow.
 * @data: Pointer to the scene data structure containing light and objects.
 * @point: Pointer to the surface point being evaluated.
 * @normal: Pointer to the surface normal at the given point.
 * @light_direction: Pointer to the direction vector from the point to
 * the light source.
 *
 * Constructs a shadow ray slightly offset from the surface point to avoid
 * self-shadowing.
 * Calculates the distance to the light source and traces the shadow ray
 * through the scene.
 * Returns 1 if the point is in shadow, 0 otherwise.
 */
int	check_shadow(t_data *data, t_vector *point, t_vector *normal,
	t_vector *light_direction)
{
	t_ray		shadow_ray;
	t_vector	offset_point;
	t_vector	light_vector;
	float		light_distance;

	offset_point = ft_scale(normal, 0.005f);
	shadow_ray.origin = ft_addition(point, &offset_point);
	shadow_ray.direction = *light_direction;
	light_vector = ft_subtraction(&data->light->origin, point);
	light_distance = ft_lenght(&light_vector);
	return (trace_shadow_ray(data, &shadow_ray, light_distance));
}
