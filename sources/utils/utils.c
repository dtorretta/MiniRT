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

// mouse rueditas tienen que cambiar el zoom que seria el ultimo elemento de la camara
void    print_menu(void)
{
	ft_printf("———————————————————————————————————————————————————————————\n");
	ft_printf("| 	  ███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗	      |\n");
	ft_printf("| 	  ████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝	      |\n");
	ft_printf("|	  ██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║   	      |\n");
	ft_printf("|	  ██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║   	      |\n");
	ft_printf("|	  ██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║   	      |\n");
	ft_printf("|	  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝        	  |\n");
	ft_printf("———————————————————————————————————————————————————————————\n");
	ft_printf("|	Press [ESC] key to exit			                 	  |\n");
	ft_printf("|	Press [W] [S] [A] or [D] to move the camera 	      |\n");
	ft_printf("|	Press [I] [K] [J] [L] [O] or [P] to move the light    |\n");
	ft_printf("|	Press [▲] [▼] [◄] [►] [+] or [-] to move objects      |\n");
	ft_printf("|	Press [C] or [V] to spin the planes                	  |\n");
	ft_printf("|	Press [Z] or [X] to spin other objects             	  |\n");
	ft_printf("|	Press [1] or [2] to resize objects                 	  |\n");
	
	
	ft_printf("|	Press [M] to show menu again		                  |\n");
	ft_printf("———————————————————————————————————————————————————————————\n");
}

void clear_image(t_data *data)
{
    int *img_data;
    int i;

    img_data = (int *)mlx_get_data_addr(data->mlx->img, &(data->mlx->bitpp), &(data->mlx->line_lenght), &(data->mlx->endian));
    i = 0;
    while (i < WIDTH * HEIGHT)
    {
        img_data[i] = 0x000000;
        i++;
    }
}

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


void	free_memory(t_data *data)
{
	if (!data)
		return ;
	free(data->amb);
	free(data->cam);
	free(data->light);

	if (data->mlx)
	{
		if (data->mlx->img)
			mlx_destroy_image(data->mlx->mlx, data->mlx->img);
		if (data->mlx->window)
			mlx_destroy_window(data->mlx->mlx, data->mlx->window);
		//if (data->mlx->mlx)
		//	mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
		free(data->mlx);
	}
	free(data);
}
