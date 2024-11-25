/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:32:38 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 23:32:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	set_node(t_data *data, char **rgb, char **origin, char	**norm)
{
	t_plane	*new_node;

	new_node = malloc(sizeof(t_plane));
	if (!new_node)
		handle_error(data, 1);
	new_node->origin.x = ft_atof(origin[0]);
	new_node->origin.y = ft_atof(origin[1]);
	new_node->origin.z = ft_atof(origin[2]);
	new_node->normal.x = ft_atof(norm[0]);
	new_node->normal.y = ft_atof(norm[1]);
	new_node->normal.z = ft_atof(norm[2]);
	new_node->color.r = ft_atoi(rgb[0]);
	new_node->color.g = ft_atoi(rgb[1]);
	new_node->color.b = ft_atoi(rgb[2]);
	if (!data->pl)
	{
		data->pl = new_node;
		data->pl->next = NULL;
	}
	else
	{
		new_node->next = data->pl;
		data->pl = new_node;
	}
}

//array[0] =  only pl
//plane array must have only 4 elements
//3d normalized normal vector valid range [-1,1]
static void	check_parameters(char **array, t_data *data)
{
	if (array[0][2] || !array[1] || !array[2] || !array[3] || array[4])
	{
		ft_free_array(array);
		handle_error(data, 8);
	}
}

void	parse_plane(char **array, t_data *data)
{
	char	**rgb;
	char	**origin;
	char	**normalized;

	check_parameters(array, data);
	rgb = ft_split(array[3], ',');
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
	normalized = ft_split(array[2], ',');
	set_node(data, rgb, origin, normalized);
	ft_free_array(rgb);
	ft_free_array(origin);
	ft_free_array(normalized);
}
