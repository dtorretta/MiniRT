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

void ft_checks (char **array)
{
	//check ambient_ratio
	//check amblight_input
	//si algo falla llama a la funcion handle_error

}

//la parte del parcing que va a ser general a todos los elementos
void parsing (char *line, t_data *data)
{
	char **array;
	
	normalize_whitespace(line); //TODO
	array = ft_split(line, ' ');
	ft_check(array);
	rm_whitespace(array); //TODO

	//aca llamamos a cada parser en particular y como argumento enviamos el array
	//dentro de cada una de estas funciones vamos a hacer el free array de cualquer NUEVO array que usemos
	
	
	ft_free_array(array); //esta en tu lbft migue
}


// funcion con el GNL TODOOOO



int parser (char *file, t_data *data)
{
	int fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(data, 0); //0 es el primero???
		
	//aca vendria una funcion con el get next line, 
	//donde va a a hacer chequeos y va aterminar llamando a la bendita funcion parsing
	
	close (fd);
	return(0);
}