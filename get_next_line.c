/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/03 18:58:42 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
char	*get_next_line(int fd)
{
	char			c;
	int				error_flag;
	static t_buffer	buffer;
	t_line			line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer.newly_created = OFF;
	error_flag = OFF;
	buffer_create(&buffer);
	line_create(&line, &error_flag);
	while (buffer_has_data(&buffer, &error_flag))
	{
		c = buffer_next_char(&buffer, fd, &error_flag);
		line_append_char(&line, c, &error_flag);
		if (c == '\n')
			break ;
		printf("line.chars = %s, buffer.bytes_read = %i\n", line.chars, buffer.bytes_read); // ###### TPO #############
	}
	//if (ft_strlen(line.chars))
	if (error_flag == ON)
	{
		line_destroy(&line);
		return (NULL);
	}
	return (line.chars);
}

/* ----------------------------- FUNC 2 ------------------------------------- */
void	buffer_create(t_buffer *buffer)
{
	if (!buffer->chars[0])
	{
		ft_bzero(buffer->chars, BUFFER_SIZE);
		buffer->write_head = BUFFER_SIZE;
		buffer->read_head = 0;
		buffer->newly_created = ON;
		buffer->bytes_read = 1;
	}
}

/* ----------------------------- FUNC 3 ------------------------------------- */
void	line_create(t_line *line, int *error_flag)
{
	line->chars = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (line->chars == NULL)
		*error_flag = ON;
	else
	{
		ft_bzero(line->chars, BUFFER_SIZE + 1);
		line->allocated = BUFFER_SIZE;
		line->filled = 0;
	}
}

/* ----------------------------- FUNC 4 ------------------------------------- */
void	line_destroy(t_line *line)
{
	if (line->chars != NULL)
	{
		free (line->chars);
		line->chars = NULL;
	}
	line->allocated = 0;
	line->filled = 0;
}
