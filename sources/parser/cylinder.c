/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:32:56 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 23:32:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	set_node2(t_cylinder *node, char **array)
{
	node->diameter = atof(array[3]);
	node->height = atof(array[4]);
}

//no importa el orden de aparicion por lo que por practicidad, cada nuevo elemento se a;ade adelante en la linked list,
//esto me permite que en set_node2, pueda directamente asignar los elementos faltantes sin tener que mover el puntero del head
static void	set_node(t_data *data, char **rgb, char **origin, char **norm)
{
	t_cylinder	*node;

	node = malloc(sizeof(t_cylinder));
	if (!node)
		handle_error(data, 1);
	node->origin.x = ft_atof(origin[0]);
	node->origin.y = ft_atof(origin[1]);
	node->origin.z = ft_atof(origin[2]);
	node->norm.x = ft_atof(norm[0]);
	node->norm.y = ft_atof(norm[1]);
	node->norm.z = ft_atof(norm[2]);
	node->color.r = ft_atoi(rgb[0]);
	node->color.g = ft_atoi(rgb[1]);
	node->color.b = ft_atoi(rgb[2]);
	if (!data->cy)
	{
		data->cy = node;
		data->cy->next = NULL;
	}
	else
	{
		node->next = data->cy;
		data->cy = node;
	}
}

//array[0] =  only cy
//sphere array must have only 6 elements
//diamenter and height cant be < 0
static void	check_parameters(char **array, t_data *data)
{
	if (array[0][2] || !array[1] || !array[2] || !array[3]
		|| !array[4] || !array[5] || array[6])
	{
		ft_free_array(array);
		handle_error(data, 8);
	}
	if (atof(array[3]) < 0 || atof(array[4]) < 0)
	{
		ft_free_array(array);
		handle_error(data, 9);
	}
}

void	parse_cylinder(char **array, t_data *data)
{
	char	**rgb;
	char	**origin;
	char	**normalized;

	check_parameters(array, data);
	rgb = ft_split(array[5], ',');
	if (check_color(rgb))
	{
		ft_free_array(array);
		handle_error(data, 4);
	}
	origin = ft_split(array[1], ',');
	normalized = ft_split(array[2], ',');
	if (check_vectors(origin, normalized, 0)
		|| check_vectors(normalized, origin, 1))
	{
		ft_free_array(rgb);
		ft_free_array(array);
		handle_error(data, 7);
	}
	set_node(data, rgb, origin, normalized);
	set_node2(data->cy, array);
	ft_free_array(rgb);
	ft_free_array(origin);
	ft_free_array(normalized);
}

//si no tuivieramos una estructura general t_data que incluya t_cylinder, el primer parametro tendria que haber sido t_cylinder *node
//y eso me hubeira obligado a declarar en parse_sphere la variable
