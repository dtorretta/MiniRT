/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:27:20 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:27:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parsing(char *line, t_data *data)
{
	char	**array;

	normalize_whitespace(line);
	array = ft_split(line, ' ');
	if (line[0] == '\n' || line[0] == '#')
		return ;
	if (line[0] == 'A')
		parse_ambient(array, data);
	if (line[0] == 'L')
		parse_light(array, data);
	if (line[0] == 'C')
		parse_camera(array, data);
	if (!ft_strncmp(line, "sp", 2))
		parse_sphere(array, data);
	if (!ft_strncmp(line, "pl", 2))
		parse_plane(array, data);
	if (!ft_strncmp(line, "cy", 2))
		parse_cylinder(array, data);
	ft_free_array(array);
}

void	read_lines(int fd, t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == 'A')
			data->amb->q++;
		if (line[0] == 'L')
			data->light->q++;
		if (line[0] == 'C')
			data->cam->q++;
		parsing(line, data);
		free(line);
	}
}

int	parser(char *file, t_data *data)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(data, 0);
	read_lines(fd, data);
	if (data->amb->q > 1 || data->light->q > 1 || data->cam->q > 1 || data->amb->q < 0 || data->light->q < 0 || data->cam->q < 0)
	{
		close (fd);
		handle_error(data, 2);
	}
	close (fd);
	return (0);
}
