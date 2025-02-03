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

//chequeo de si el argv[1] que es el nombre del file, sea .rt. sino
//ft_strncmp returns 1 if coincidence
int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file) - 3;
	return (ft_strncmp(file + len, ".rt", 3));
}

void	init_data(t_data *data)
{
	data->sp = NULL;
	data->pl = NULL;
	data->cy = NULL;
	data->qdtc = malloc(sizeof(t_quadratic));
	data->light = malloc(sizeof(t_light));
	data->amb = malloc(sizeof(t_ambient));
	data->cam = malloc(sizeof(t_camera));
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->light || !data->amb || !data->cam || !data->mlx || !data->qdtc)
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
