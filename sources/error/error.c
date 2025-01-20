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

int	handle_error(t_data *data, int error)
{
	const char	*message;
	const char	*error_message[] = {
		"system error: error in fd\n", // 0
		"Failed to allocate memory for data\n", // 1
		"Error: additional  A, L or C\n", // 2
		"Error: valid ratio range [0.0,1.0]\n", // 3
		"Error: valid colors range [0-255]\n", // 4
		"Error: wrong ambient's paramenters\n", // 5
		"Error: wrong light's paramenters\n", // 6
		"Error: invalid x,y,z coordinates\n", // 7
		"Error: wrong sphere's paramenters\n", // 8
		"Error: Invalid diameter or height\n", // 9
		"Error: wrong camera's parameters\n", // 10
		"Error: invalid camera FOV\n", // 11
	};
	message = error_message[error];
	ft_putstr_fd(message, 2);
	free_memory(data);
	exit(EXIT_FAILURE);
}


int	handle_error2(t_data *data, int error)
{
	const char	*message;
	const char	*error_message[] = {
		"Error: Failed connecting to MLX\n", // 0
		"Error: Failed creating window\n", // 1
		"Error: Failed creating image\n", // 2
		"Error: Failed receiving image information", // 3
	};

	message = error_message[error];
	ft_putstr_fd(message, 2);
	free_memory(data);
	exit(EXIT_FAILURE);
}

