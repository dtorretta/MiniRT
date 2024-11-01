/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:20:59 by dtorrett          #+#    #+#             */
/*   Updated: 2024/11/01 23:19:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*----------------------------------------------------------------------------*/
/* This function finds the length of the first line in buffer, allocates      */
/* memory for the rest of the file after the first line, copies that content  */
/* to the new line buffer, frees the original buffer, and returns the new     */
/* line.                                                                      */
/*----------------------------------------------------------------------------*/

char	*obtain_rest(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

/*----------------------------------------------------------------------------*/
/* This function finds the length of the line in the buffer, allocates memory */
/* for the line plus an additional character ('\n'), copies the content to    */
/* the new line, and appends a '\0' character at the end of the line.         */
/*----------------------------------------------------------------------------*/

char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/* -------------------------------------------------------------------------- */
/* This function appends the read buffer data to the content_buffer (which is */
/* the static_buffer) using ft_strjoin, frees the original "content_buffer",  */
/* and returns a newly created string "temp".                                 */
/* -------------------------------------------------------------------------- */

char	*ft_join_free(char *content_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(content_buffer, read_buffer);
	free (content_buffer);
	return (temp);
}

/* -------------------------------------------------------------------------- */
/* This function reads from the file descriptor into "size_buffer", appends   */
/* it into the existing content of "content_buffer" and continues reading     */
/* until a '\n' is found. It returns the final content.                       */
/* -------------------------------------------------------------------------- */

char	*read_from_file(char *content_buffer, int fd)
{
	char	*size_buffer;
	int		bytes_read;

	if (!content_buffer)
		content_buffer = ft_calloc(1, sizeof(char));
	size_buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, size_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(content_buffer);
			return (NULL);
		}
		size_buffer[bytes_read] = 0;
		content_buffer = ft_join_free(content_buffer, size_buffer);
		if (ft_strchr(size_buffer, '\n'))
			break ;
	}
	free(size_buffer);
	return (content_buffer);
}

/* -------------------------------------------------------------------------- */
/* This function maintains a static buffer between function calls, reads the  */
/* file content using read_from_file, extracts the next line using            */
/* extract_line, and updates the buffer using obtain_rest.                    */
/* It returns the extracted line.                                             */
/* -------------------------------------------------------------------------- */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_buffer;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_buffer = read_from_file(static_buffer, fd);
	if (!static_buffer)
		return (NULL);
	line = extract_line(static_buffer);
	static_buffer = obtain_rest(static_buffer);
	return (line);
}

// static char	*set_line(char **line_buffer)
// {
// 	char	*remaining;
// 	char	*temp;

// 	temp = ft_strchr(*line_buffer, '\n');
// 	if (!temp++)
// 		return (NULL);
// 	remaining = ft_strdup(temp);
// 	*temp = '\0';
// 	return (remaining);
// }

// static char	*set_buffer(int fd, char *left_c, char *tempbuf)
// {
// 	int	bytesread;

// 	while (!ft_strchr(left_c, '\n'))
// 	{
// 		bytesread = read(fd, tempbuf, BUFFER_SIZE);
// 		if (bytesread == -1)
// 		{
// 			free(left_c);
// 			return (NULL);
// 		}
// 		if (bytesread == 0)
// 			break ;
// 		tempbuf[bytesread] = '\0';
// 		left_c = ft_strjoin(left_c, tempbuf);
// 	}
// 	free(tempbuf);
// 	return (left_c);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*buffer[MAX_FD];
// 	char		*tempbuf;

// 	tempbuf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!tempbuf || fd < 0 || BUFFER_SIZE <= 0)
// 	{
// 		free(tempbuf);
// 		free(buffer[fd]);
// 		return (NULL);
// 	}
// 	line = set_buffer(fd, buffer[fd], tempbuf);
// 	buffer[fd] = set_line(&line);
// 	return (line);
// }

// int	main(void)
// {
// 	int		fd1;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	fd1 = open("dict.txt", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		return (1);
// 	}
// 	while (i < 2)
// 	{
// 		line = get_next_line(fd1);
// 		if (line == NULL)
// 			break ;
// 		printf("get line %d: %s", i + 1, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }
