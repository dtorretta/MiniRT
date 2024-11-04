/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:52:10 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:52:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*Hacemos un free*/
int	handle_error(t_data *data, int error)
{
	//(void)data; //borrar
	const char	*message;
	const char	*error_message[] = {
		"system error: error in fd\n", // 0
		"Failed to allocate memory for data\n" // 1
		"Error: A, L or C missing\n" // 2
		"Error: valid ratio range [0.0,1.0]\n" // 3
		"Error: valid colors range [0-255]\n" // 4
		"Error: wrong ambient's paramenters\n" // 5
		"Error: wrong light's paramenters\n" // 6
		"Error: invalid x,y,z coordinates\n" // 7
		"Error: wrong sphere's paramenters\n" // 8
		"Error: Invalid diameter\n" // 9
		"Error: Failed connecting to MLX\n", // 10
		"Error: Failed creating window\n" // 11
		"Error: Failed creating image\n" // 12
		"Error: Failed receiving image information" // 13
	};

	message = error_message[error];
	ft_putstr_fd(message, 2);
	free_memory(data);
	return (EXIT_FAILURE);
}
