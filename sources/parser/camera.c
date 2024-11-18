/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:32:16 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 23:32:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	check_parameters(char **array, t_data *data)
{
	if (array[0][1] || !array[1] || !array[2] || !array[3] || array[4])
	{
		ft_free_array(array);
		handle_error(data, 10);
	}
	if (atof(array[3]) < 0 || atof(array[3]) > 180)
	{
		ft_free_array(array);
		handle_error(data, 11);
	}
}

void	parse_camera(char **array, t_data *data)
{
	char	**view;
	char	**vector;

	check_parameters(array, data);
	view = ft_split(array[1], ',');
	vector = ft_split(array[2], ',');
	if (check_vectors(view, vector, 0) || check_vectors(vector, view, 1))
	{
		ft_free_array(array);
		handle_error(data, 7);
	}
	data->cam->origin.x = atof(view[0]);
	data->cam->origin.y = atof(view[1]);
	data->cam->origin.z = atof(view[2]);
	data->cam->aim.x = atof(vector[0]);
	data->cam->aim.y = atof(vector[1]);
	data->cam->aim.z = atof(vector[2]);
	data->cam->fov = atof(array[3]);
	ft_free_array(view);
	ft_free_array(vector);
}
