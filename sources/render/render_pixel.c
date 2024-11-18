/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:21:26 by miguandr          #+#    #+#             */
/*   Updated: 2024/11/18 19:08:47 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Draws a pixel at the specified coordinates with the given color.
 * @mlx: Pointer to the graphics structure containing image information.
 * @x: X-coordinate of the pixel.
 * @y: Y-coordinate of the pixel.
 * @color: Color value in 32-bit integer format (TRGB).
 *
 * This function calculates the memory address of the pixel within the image
 * buffer using the coordinates and the structure's properties. It then sets
 * the pixel's color by writing the value to the calculated address.
 */
static void	my_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel_address;

	pixel_address = mlx->address + (y * mlx->line_lenght)
		+ (x * (mlx->bitpp / 8));
	*(unsigned int *)pixel_address = color;
}

/**
 * Combines alpha, red, green, and blue color components into a single value.
 * @alpha: Transparency value (0-255).
 * @red: Red color intensity (0-255).
 * @green: Green color intensity (0-255).
 * @blue: Blue color intensity (0-255).
 *
 * Each color component is masked to ensure it is within the 0-255 range, then
 * shifted into its respective position within a 32-bit integer. The result is
 * a single TRGB color value suitable for rendering.
 * @return: A 32-bit integer representing the combined TRGB color.
 */
int	create_color(int alpha, int red, int green, int blue)
{
	return ((alpha & 0xFF) << 24 | (red & 0xFF) << 16
		| (green & 0xFF) << 8 | (blue & 0xFF));
}

/**
 * Computes the final color by combining base color, diffuse lighting,
 * and ambient light.
 * @base_color: The object's inherent color as a t_color struct.
 * @diffuse: The diffuse lighting factor (0.0 to 1.0).
 * @ambient: The ambient color contribution as a t_color struct.
 *
 * Each color channel (red, green, blue) is calculated by multiplying the base
 * color by the diffuse factor and adding the ambient contribution. The resulting
 * values are clamped to the maximum value of 255 to ensure valid color output.
 * @return: A t_color struct representing the final color.
 */
t_color	calculate_color(t_color base_color, float diffuse, t_color ambient)
{
	t_color	result;

	result.r = (int)(base_color.r * diffuse + ambient.r);
	result.g = (int)(base_color.g * diffuse + ambient.g);
	result.b = (int)(base_color.b * diffuse + ambient.b);

	result.r = fminf(result.r, 255);
	result.g = fminf(result.g, 255);
	result.b = fminf(result.b, 255);

	return (result);
}

/**
 * Retrieves the color of the given object, considering lighting effects.
 * @figure: The object being rendered, containing its color and type.
 * @diffuse: The diffuse lighting factor affecting the object (0.0 to 1.0).
 * @ambient: The ambient color contribution as a t_color struct.
 *
 * Based on the type of object (sphere, plane, or cylinder), the function
 * retrieves the object's base color and computes the final color using
 * `calculate_color`. If no object is specified, it returns black.
 * @return: A t_color struct representing the object's final color.
 */
t_color	get_object_color(t_figure figure, float diffuse, t_color ambient)
{
	if (figure.sphere)
		return (calculate_color(figure.sphere->color, diffuse, ambient));
	else if (figure.plane)
		return (calculate_color(figure.plane->color, diffuse, ambient));
	else if (figure.cylinder)
		return (calculate_color(figure.cylinder->color, diffuse, ambient));
	return ((t_color){0, 0, 0});
}

/**
 * Calculates and renders the color of a pixel based on lighting and object properties.
 * @data: Pointer to the main data structure containing scene and rendering information.
 * @x: X-coordinate of the pixel to render.
 * @y: Y-coordinate of the pixel to render.
 * @figure: The object intersected by the ray, containing its properties and color.
 *
 * The function first computes the light direction vector and normalizes it. It
 * calculates the ambient lighting contribution and checks whether the object
 * is in shadow. If the object is not in shadow, the diffuse lighting is calculated.
 * The object's color is determined using `get_object_color`, and the resulting color
 * is converted to a TRGB value using `create_color`. Finally, the pixel is rendered
 * on the screen using `my_put_pixel`.
 */
void	generate_pixel_color(t_data *data, int x, int y, t_figure figure)
{
	t_vector	light_direction;
	t_color		ambient_color;
	t_color		final_color;
	float		diffuse;
	int			trgb;

	ambient_color = (t_color){0, 0, 0};
	diffuse = 0.0f;
	// Calculate light direction and check for shadows
	light_direction = ft_subtraction(&data->light->origin, &figure.intersection);
	light_direction = ft_normalize(&light_direction);
	ft_calculate_ambient_lighting(data, &ambient_color); // TODO
	if (!ft_is_in_shadow(data, &figure.intersection, // TODO
			&figure.normal, &light_direction))
		diffuse = calculate_diffuse_lighting(&figure.normal, &light_direction); //TODO

	// Get final color and render pixel
	final_color = get_object_color(figure, diffuse, ambient_color);
	trgb = create_color(255, final_color.r, final_color.g, final_color.b);
	my_put_pixel(data->mlx, x, y, trgb);
}
