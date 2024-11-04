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

static void	checks(char **array, t_data *data)
{
	if (array[0][1] || !array[1] || !array[2] || !array[3])
}

void	parse_camera(char **array, t_data *data)
{
	char	**view;
	char	**vector;

	checks(array, data);
	view = ft_split(array[1], ',');
}
