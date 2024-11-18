/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:24:06 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 21:24:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	keyboard_exit(int keysym, t_data *data)
{
	// keysym 53 is for mac. DELETE later
	if (keysym == 0xFF1B || keysym == 53)
	{
		free_memory(data);
		exit (0);
	}
	return (0);
}

int	mouse_exit(t_data *data)
{
	free_memory(data);
	exit (0);
	return (0);
}
