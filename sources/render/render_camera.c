/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:02:24 by miguandr          #+#    #+#             */
/*   Updated: 2024/11/25 21:34:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	calculate_camera_basis(t_camera *camera)
{
	t_vector	up_reference;
	t_vector	right_vector;
	t_vector	up_vector;

	up_reference = (t_vector){0.0f, 1.0f, 0.0f};
	// Adjust default_up if direction is pointing straight up or down
	if (fabs(camera->aim.x) < 1e-6 && fabs(camera->aim.z) < 1e-6)
	{
		up_reference.x = 1.0f;
		up_reference.y = 0.0f;
		up_reference.z = 0.0f;
	}
	// Calculate camera basis vectors
	right_vector = ft_cross(&camera->aim, &up_reference);
	camera->right = ft_normalize(&right_vector);
	up_vector = ft_cross(&camera->right, &camera->aim);
	camera->up = ft_normalize(&up_vector);
}

void	calculate_pixel00(t_camera *camera,
	t_vector viewport_x, t_vector viewport_y)
{
	t_vector	focal_point;
	t_vector	top_left_corner;
	t_vector	temp_scaled_x;
	t_vector	temp_scaled_y;

	//Calculate focal point based on the focal length
	focal_point = ft_scale(&camera->aim, camera->focal_length);

	//Calculate top-left corner of the viewport
	top_left_corner = ft_addition(&camera->origin, &focal_point);

	// Scale the viewport vectors by 0.5
	temp_scaled_x = ft_scale(&viewport_x, 0.5f);
	temp_scaled_y = ft_scale(&viewport_y, 0.5f);
	top_left_corner = ft_subtraction(&top_left_corner, &temp_scaled_x);
	top_left_corner = ft_subtraction(&top_left_corner, &temp_scaled_y);

	// Calculate pixel (0, 0) location with pixel deltas
	camera->pixel00_location = ft_addition(&camera->pixel_delta_x,
			&camera->pixel_delta_y);
	camera->pixel00_location = ft_scale(&camera->pixel00_location, 0.5f);
	camera->pixel00_location = ft_addition(&top_left_corner,
			&camera->pixel00_location);
}

void	init_camera(t_camera *camera)
{
	t_vector	viewport_x;
	t_vector	viewport_y;
	float		aspect_ratio;
	float		viewport_height;
	float		viewport_width;

	// Normalize camera direction and convert FOV to radians
	camera->aim = ft_normalize(&camera->aim);
	camera->focal_length = 1.0f;
	camera->fov *= 3.14159265358979323846 / 180.0f;
	calculate_camera_basis(camera);
	//viewport dimensions
	aspect_ratio = (float)HEIGHT / (float)WIDTH;
	viewport_width = 2.0f * tan(camera->fov / 2.0f);
	viewport_height = viewport_width * aspect_ratio;
	//calculate viepor vectors
	viewport_x = ft_scale(&camera->right, viewport_width);
	viewport_y = ft_scale(&camera->up, -viewport_height); // Invert Y for screen space
	//Calculate distance between pixels
	camera->pixel_delta_x = ft_scale(&viewport_x, 1.0f / (float)WIDTH);
	camera->pixel_delta_y = ft_scale(&viewport_y, 1.0f / (float)HEIGHT);
	//Calculate location of the first pixel
	calculate_pixel00(camera, viewport_x, viewport_y);
}
