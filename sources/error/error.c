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
	(void)data;
	const char	*message;
	const char	*error_message[] = {
		"system error: error in fd\n",  //ok
	};

	message = error_message[error];
	ft_putstr_fd(message, 2);
	//free(data);	//TO DO
	return (EXIT_FAILURE);
}