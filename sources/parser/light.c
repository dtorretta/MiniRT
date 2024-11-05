/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:32:04 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 23:32:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//array[0] =  only L
//ambient array must have only 3 elements
//valid light brightness ratio range [0.0,1.0]:
static void	check_parameters(char **array, t_data *data)
{
	if (array[0][1] || !array[1] || !array[2] || array[3])
	{
		ft_free_array(array);
		handle_error(data, 6);
	}
	if (atof(array[2]) < 0 || atof(array[2]) > 1)
	{
		ft_free_array(array);
		handle_error(data, 3);
	}
}

void	parse_light(char **array, t_data *data)
{
	char	**origin;

	check_parameters(array, data);
	origin = ft_split(array[1], ',');
	if (check_vectors(origin, 0))
	{
		ft_free_array(array);
		handle_error(data, 7);
	}
	data->light->ratio = ft_atof(array[2]);
	data->light->origin.x = ft_atof(origin[0]);
	data->light->origin.y = ft_atof(origin[1]);
	data->light->origin.z = ft_atof(origin[2]);
	ft_free_array(origin);
}
