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

size_t	ft_strlen(const char *s) //borrar
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	ft_putstr_fd(char *s, int fd)//borrar
{
	if (!s)
		return ;
	else
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)//borrar
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n) //BORRAR
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ptr1[i] == ptr2[i] && (ptr1[i] || ptr2[i]) && i < n - 1)
		i++;
	return (ptr1[i] - ptr2[i]);
}

//es necesario hacer este chequeo?? o simplemente con que no funcione el open estamos?
//chequeo de si el argv[1] que es el nombre del file, sea .rt. sino 
//ft_strncmp returns 1 if coincidence
int check_extension (char *file) //se puede pooner en otro file
{
	int len;
	
	len = ft_strlen(file) - 3;
	return(ft_strncmp(file + len, ".rt", 3));	
}

void init_data(t_data *data)
{
	//aca para cada elemento de la estructura general, vamos a asignar malloc e iniciarlo en NULL
}

int main (int ac, char **av)
{
	t_data *data;
	
	if(ac != 2)
		return(ft_putendl_fd("Error: Invalid number of arguments", 2), 1);
	if(check_extension(av[1]))
		return(ft_putendl_fd("Error: Invalid file extension", 2), 1);
	data = malloc(sizeof(t_data));
	if(!data)
		return(ft_putendl_fd("Failed to allocate memory for data", 2), 1);
	
	init_data(data); //TO DO
	parser(av[1], data); //TO DO
	lauch_mlx(data); //TO DO
	
	return(0);
}