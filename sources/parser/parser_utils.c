/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:25:56 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 22:25:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//only can be 3 colors (RGB) and they must be [0,255];
int	check_color(char **rgb)
{
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_array(rgb);
		return (1);
	}
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) > 255)
	{
		ft_free_array(rgb);
		return (1);
	}
	return (0);
}

int	check_vectors(char **xyz, char **to_free, int flag)
{
	if (!xyz[0] || !xyz[1] || !xyz[2] || xyz[3])
	{
		ft_free_array(xyz);
		ft_free_array(to_free);
		return (1);
	}
	if (flag == 1)
	{
		if (atof(xyz[0]) < -1 || atof(xyz[0]) > 1 || atof(xyz[1]) < -1
			|| atof(xyz[1]) > 1 || atof(xyz[2]) < -1 || atof(xyz[2]) > 1)
		{
			ft_free_array(xyz);
			ft_free_array(to_free);
			return (1);
		}
	}
	return (0);
}
