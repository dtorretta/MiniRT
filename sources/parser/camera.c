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

/*∗ identifier: C
∗array[1]: x,y,z coordinates of the view point: -50.0,0,20
∗array[2]: 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗array[3]: FOV : Horizontal field of view in degrees in range [0,180]: 70*/

/*!!!!!!AGREGAR FUNCION CHECK_VECTORS!!!!!!*/
static int	check_camera(char **view, char **vector)
{
	if (!view[0] || !view[1] || !view[2] || view[3])
		return (1);
	if (!vector[0] || !vector[1] || !vector[2] || vector[3])
		return (1);
	if (atof(vector[0]) < -1 || atof(vector[0]) > 1 || atof(vector[1]) < -1
		|| atof(vector[1]) > 1 || atof(vector[2]) < -1 || atof(vector[2]) > 1)
		return (1);
	return (0);
}

static void	checks(char **array, t_data *data)
{
	if (array[0][1] || !array[1] || !array[2] || !array[3] || array[4])
	{
		ft_free_array(array);
		handle_error(data, 10);
	}
	if (atof(array[3]) < 0 || atof(array[3]) > 180)
	{
		ft_free_array(array);
		handle_error(data, 11); // agregar a handle_error: "invalid camera FOV\n"
	}
}

/*AGREGAR AL HEADER!!!!!!!!!!*/
void	parse_camera(char **array, t_data *data)
{
	char	**view;
	char	**vector;

	checks(array, data);
	view = ft_split(array[1], ',');
	vector = ft_split(array[2], ',');
	if (check_camera(view, vector))
	{
		ft_free_array(view);
		ft_free_array(vector);
		ft_free_array(array);
		handle_error(data, 12); // agregar a handle_error: "Invalid camera view point or vector\n"
	}
	data->cam->origin.x = atof(view[0]);
	data->cam->origin.y = atof(view[1]);
	data->cam->origin.z = atof(view[2]);
	data->cam->orientation.x = atof(vector[0]);
	data->cam->orientation.y = atof(vector[1]);
	data->cam->orientation.z = atof(vector[2]);
	data->cam->fov = atof(array[3]);
	ft_free_array(view);
	ft_free_array(vector);
	ft_free_array(array);
}
