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
	(void)data; //borrar
	char	*message;
	char	*error_message[] = {
		"system error: error in fd\n",
		"Failed to allocate memory for data\n"
		"Error: A, L or C missing\n"
		"Error: valid ratio range [0.0,1.0]\n"
		"Error: valid colors range [0-255]\n"
		"Error: wrong ambient's paramenters\n"
		"Error: wrong light's paramenters\n"
		"Error: invalid x,y,z coordinates\n"
		"Error: wrong sphere's paramenters\n"
		"Error: Invalid diameter\n"
	};

	message = error_message[error];
	ft_putstr_fd(message, 2);
	//free(data);	//TO DO no tienen que liberar el array
	return (EXIT_FAILURE);
}