/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:32:29 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 23:32:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	set_node(t_data *data, char **array, char **rgb, char **origin)
{
	t_sphere	*new_node;
	t_sphere	*temp;

	new_node = malloc(sizeof(t_sphere));
	if (!new_node)
		handle_error(data, 1);
	new_node->origin.x = ft_atof(origin[0]);
	new_node->origin.y = ft_atof(origin[1]);
	new_node->origin.z = ft_atof(origin[2]);
	new_node->diameter = ft_atof(array[2]);
	new_node->color.r = ft_atoi(rgb[0]);
	new_node->color.g = ft_atoi(rgb[1]);
	new_node->color.b = ft_atoi(rgb[2]);
	if (!data->sp)
		data->sp = new_node;
	else
	{
		temp = data->sp;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

//only can be 3 colors (RGB) and they must be [0,255];
static int	check_color(char **array)
{
	if (!array[0] || !array[1] || !array[2] || array[3])
	{
		ft_free_array(array);
		return (1);
	}
	if (ft_atoi(array[0]) < 0 || ft_atoi(array[1]) < 0
		|| ft_atoi(array[2]) < 0 || ft_atoi(array[0]) > 255
		|| ft_atoi(array[1]) > 255 || ft_atoi(array[2]) > 255)
	{
		ft_free_array(array);
		return (1);
	}
	return (0);
}

//only can be 3 coordinates (x,y,z)
static int	check_origin(char **origin, char **rgb)
{
	if (!origin[0] || !origin[1] || !origin[2] || origin[3])
	{
		ft_free_array(origin);
		ft_free_array(rgb);
		return (1);
	}
	return (0);
}

//array[0] =  only sp
//sphere array must have only 4 elements
//diamenter cant be < 0
static void	check_parameters(char **array, t_data *data)
{
	if (array[0][2] || !array[1] || !array[2] || !array[3] || array[4])
	{
		ft_free_array(array);
		handle_error(data, 8);
	}
	if (atof(array[1]) < 0)
	{
		ft_free_array(array);
		handle_error(data, 9);
	}
}

void	parse_sphere(char **array, t_data *data)
{
	char	**rgb;
	char	**origin;

	check_parameters(array, data);
	rgb = ft_split(array[3], ',');
	if (check_color(rgb))
		handle_error(data, 4);
	origin = ft_split(array[1], ',');
	if (check_origin(origin, rgb))
		handle_error(data, 7);
	set_node(data, array, rgb, origin);
	ft_free_array(rgb);
	ft_free_array(origin);
}
