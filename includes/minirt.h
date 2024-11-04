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
//# include <X11/X.h>
# include "../minilibx/mlx.h"

/*-Macros-*/
# define HEIGHT 1200
# define WIDTH 800
# define FINISH_EVENT 17

/*Color Structure*/
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}					t_color;

/*Vector Structure*/
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

/*Ambient Structure*/
typedef struct s_ambient
{
	int		q;
	float	ratio;
	t_color	color;
}					t_ambient;

/*Light Structure*/
typedef struct s_light
{
	int			q;
	float		ratio;
	t_vector	origin;
}					t_light;

/*Camera Structure*/
typedef struct s_camera
{
	int			q;
	float		fov;
	t_vector	origin;
	t_vector	orientation; //direccion
}					t_camera;

/*Sphere Structure*/
typedef struct s_sphere
{
	t_vector		origin;
	t_color			color;
	float			diameter;
	struct s_sphere	*next;
}					t_sphere;

/*Plane Structure*/
typedef struct s_plane
{
	//TODO
	struct s_sphere	*next;
}					t_plane;

/*Cylinder Structure*/
typedef struct s_cylinder
{
	//TODO
	struct s_sphere	*next;
}					t_cylinder;

/*MLX Structure*/
typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*address;
	int			line_lenght;
	int			endian;
	int			bitpp;
}					t_mlx;

/*Data Structure*/
typedef struct s_data
{
	t_mlx		*mlx;
	t_ambient	*amb;
	t_light		*light;
	t_camera	*cam;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
}					t_data;


int	handle_error(t_data *data, int error);
int parser (char *file, t_data *data);
void normalize_whitespace(char *str);


void parse_ambient(char **array, t_data *data);
void parse_light(char **array, t_data *data);

void parse_sphere(char **array, t_data *data);

void	ft_render(t_data *data)

#endif
