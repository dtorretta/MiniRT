/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:31:36 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 23:31:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//only can be 3 colors (RGB) and they must be [0,255];
int check_color(char **array)
{
	if(!array[0] || !array[1] || !array[2] || array[3])
	{
		ft_free_array(array);
		return(1);
	}
	if(ft_atoi(array[0]) < 0 || ft_atoi(array[1]) < 0 || ft_atoi(array[2]) < 0 
			|| ft_atoi(array[0]) > 255 || ft_atoi(array[1]) > 255 
			|| ft_atoi(array[2]) > 255)
	{
		ft_free_array(array);
		return(1);
	}	
	return(0);
}

//array[0] =  only A
//ambient array must have only 3 elements
//valid ambient lighting ratio range [0.0,1.0]:
void checks(char **array, t_data *data)
{
	if(array[0][1] || !array[1] || !array[2] || array[3])
	{
		ft_free_array(array);
		handle_error(data, 5);
	}
	if(atof(array[1]) < 0 || atof(array[1]) > 1)
	{
		ft_free_array(array);
		handle_error(data, 3);
	}
}

void parse_ambient(char **array, t_data *data)
{
	char **rgb;
	
	checks(array, data);
	rgb = ft_split(array[2], ',');  
	if(check_color(rgb))
		handle_error(data, 4);
	data->amb->ratio = ft_atof(array[1]);
	data->amb->color.r = ft_atoi(rgb[0]);
	data->amb->color.g = ft_atoi(rgb[1]);
	data->amb->color.b = ft_atoi(rgb[2]);
	ft_free_array(rgb);
}
