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

//only can be 3 coordinates (x,y,z)
int	check_origin(char **array)
{
	if (!array[0] || !array[1] || !array[2] || array[3])
	{
		ft_free_array(array);
		return (1);
	}
	return (0);
}

//array[0] =  only L
//ambient array must have only 3 elements
//valid light brightness ratio range [0.0,1.0]:
void	checks(char **array, t_data *data)
{
	if (array[0][1] || !array[1] || !array[2] || !array[3])
	{
		ft_free_array(array);
		handle_error(data, 6);
	}
	if (atof(array[1]) < 0 || atof(array[1]) > 1)
	{
		ft_free_array(array);
		handle_error(data, 3);
	}
}

void	parse_light(char **array, t_data *data)
{
	char	**origin;

	checks(array, data);
	origin = ft_split(array[1], ',');
	if (check_origin(origin))
		handle_error(data, 7);
	data->light->ratio = ft_atof(array[2]);
	data->light->origin.x = ft_atof(origin[0]);
	data->light->origin.y = ft_atof(origin[1]);
	data->light->origin.z = ft_atof(origin[2]);
	ft_free_array(origin);
}
