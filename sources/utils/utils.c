/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:36:37 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 22:36:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//reescribe el char *str original en lugar de crear una copia nueva,
//eliminado los espacios en blanco adicionales
void	normalize_whitespace(char *str)
{
	int	i;
	int	j;
	int	space;

	i = 0;
	j = 0;
	space = 0;
	while (str[i])
	{
		if (!ft_iswhitespace((unsigned char)str[i]))
		{
			str[j++] = str[i++];
			space = 0;
		}
		else if (!space)
		{
			str[j++] = ' ';
			space = 1;
			i++;
		}
		else
			i++;
	}
	str[j] = '\0';
}


