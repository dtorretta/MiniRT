/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:17:40 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 15:17:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector ft_addition(t_vector *a, t_vector *b)
{
	t_vector result;
	
	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return(result);
}

t_vector ft_subtraction(t_vector *a, t_vector *b)
{
	t_vector result;
	
	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return(result);
}

t_vector ft_cross(t_vector *a, t_vector *b)
{
	t_vector result;
	
	result.x = a->y * b->z - a->z * b->y;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;	
	return(result);
}

//funcion to calculate the scalar of 2 vector
float ft_dot(t_vector *a, t_vector *b)
{
	float result;
	
	result = a->x * b->x + a->y * b->y + a->z * b->z;	
	return(result);
}

t_vector ft_normalize(t_vector *a)
{
	t_vector result;
	float lenght;
	
	lenght = ft_lenght(a);	
	result.x = a->x / lenght;
	result.y = a->y / lenght;
	result.z = a->z / lenght;
	return(result);
}

