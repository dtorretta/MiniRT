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


typedef struct s_ambient
{
	int q;
}					t_ambient;

typedef struct s_light
{
	int q;
}					t_light;

typedef struct s_camera
{
	int q;
}					t_camera;

typedef struct s_data
{
	t_ambient *amb;
	t_light *light;
	t_camera *cam;
}					t_data;






int	handle_error(t_data *data, int error);
int parser (char *file, t_data *data);
void normalize_whitespace(char *str);




#endif