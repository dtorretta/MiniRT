/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:11:11 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:11:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//es necesario hacer este chequeo?? o simplemente con que no funcione el open estamos?
//chequeo de si el argv[1] que es el nombre del file, sea .rt. sino
//ft_strncmp returns 1 if coincidence
int	check_extension(char *file) //se puede pooner en otro file
{
	int	len;

	len = ft_strlen(file) - 3;
	return (ft_strncmp(file + len, ".rt", 3));
}

//al final si es necesario primero incializarlo en null y despues asignarle malloc
void	init_data(t_data *data)
{
	//data->light = NULL;
	//data->amb = NULL;
	//data->cam = NULL;
	data->sp = NULL;
	data->pl = NULL;
	data->cy = NULL;
	//data->mlx = NULL;
	data->light = malloc(sizeof(t_light));
	data->amb = malloc(sizeof(t_ambient));
	data->cam = malloc(sizeof(t_camera));
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->light || !data->amb || !data->cam || !data->mlx)
		handle_error(data, 1);
	data->light->q = 0;
	data->amb->q = 0;
	data->cam->q = 0;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (ft_putendl_fd("Error: Invalid number of arguments", 2), 1);
	if (check_extension(av[1]))
		return (ft_putendl_fd("Error: Invalid file extension", 2), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putendl_fd("Failed to allocate memory for data", 2), 1);
	init_data(data);
	parser(av[1], data);
	render(data);

	return (0);
}

/*
cc -Wall -Wextra -Werror -I ./includes -I ./libft/includes -I /usr/include/readline main.c ./parser/parser.c ./error/error.c ./utils/utils.c -L ../libft -lft -L /usr/lib -lreadline -o test
*/
