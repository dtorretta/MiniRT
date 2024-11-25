/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:28:56 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 15:28:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	ft_lenght(t_vector *a)
{
	float	result;

	result = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	return (result);
}

t_vector	ft_scale(t_vector *a, float scalar)
{
	t_vector	result;

	result.x = a->x * scalar;
	result.y = a->y * scalar;
	result.z = a->z * scalar;
	return (result);
}

t_vector	ft_perpendicular(t_vector *a, t_vector *b)
{
	t_vector	perpendicular;
	float		scalar;
	t_vector	scaled;

	scalar = ft_dot(a, b);
	scaled = ft_scale(b, scalar);
	perpendicular = ft_subtraction(a, &scaled);
	return (perpendicular);
}
