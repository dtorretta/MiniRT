/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:12:28 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:12:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>


typedef struct s_color
{
	int r;
	int g;
	int b;
}					t_color;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

typedef struct s_ambient
{
	int q;
	float ratio;
	t_color color;
}					t_ambient;

typedef struct s_light
{
	int q;
	t_vector origin;
	float ratio;
}					t_light;

typedef struct s_camera
{
	int q;
	t_vector origin;
	t_vector orientation; //direccion
	float fov;
}					t_camera;

typedef struct s_sphere
{
	t_vector origin;
	float diameter;
	t_color color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	//TODO
	struct s_sphere	*next;
}					t_plane;

typedef struct s_cylinder
{
	//TODO
	struct s_sphere	*next;
}					t_cylinder;

typedef struct s_data
{
	t_ambient *amb;
	t_light *light;
	t_camera *cam;
	t_sphere *sp;
	t_plane *pl;
	t_cylinder *cy;	
}					t_data;



int	handle_error(t_data *data, int error);
int parser (char *file, t_data *data);
void normalize_whitespace(char *str);


void parse_ambient(char **array, t_data *data);
void parse_light(char **array, t_data *data);

void parse_sphere(char **array, t_data *data);

#endif