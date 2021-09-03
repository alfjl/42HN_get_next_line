/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/03 11:05:15 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	int				bytes_read;
	static t_buffer	buffer;
	t_line			line;

	// ---------- Guard Pattern ----------------------
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// ---------- Variable Initialization Pattern ----
	bytes_read = 1;
	buffer.newly_created = __OFF__;
	buffer_create(&buffer);
	if (line_create(&line) == 0)
		return (NULL);
	while (bytes_read >= 0)
	{
		if (buffer_write(&buffer, &line, &bytes_read, fd) == -1)
			return (NULL);
		line_write(&line, &buffer);
		if (line.chars[line.filled - 1] == '\n')
			break ;
		if (bytes_read == 0 && buffer.chars[buffer.read_head] == '\0')
			break ;
	}
	if (line_determine_null(&line) == 0)
		return (NULL);
	return (line.chars);
}

/* ----------------------------- FUNC 2 ------------------------------------- */
void	buffer_create(t_buffer *buffer)
{
	// if (buffer->chars == NULL) // checks Pointer, not content!
	// if (buffer->chars[0] == 0)
	// if (buffer->chars[0] == '\0')
	if (!buffer->chars[0]) // change to correct test phrase! Don't use "!"
	{
		ft_bzero(buffer->chars, BUFFER_SIZE);
		buffer->write_head = BUFFER_SIZE;
		buffer->read_head = 0;
		buffer->newly_created = __ON__;
	}
}

/* ----------------------------- FUNC 3 ------------------------------------- */
int	line_create(t_line *line)
{
	line->chars = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (line->chars == NULL)
		return (0);
	ft_bzero(line->chars, BUFFER_SIZE + 1);
	line->allocated = BUFFER_SIZE;
	line->filled = 0;
	return (1);
}

/* ----------------------------- FUNC 4 ------------------------------------- */
int	buffer_write(t_buffer *buffer, t_line *line, int *bytes_read, int fd)
{
	if (buffer->newly_created == __ON__
		|| buffer->read_head >= buffer->write_head)
	{
		*bytes_read = read(fd, buffer->chars, BUFFER_SIZE);
		buffer->read_head = 0;
		buffer->write_head = *bytes_read;
		buffer->chars[*bytes_read] = '\0';
	}
	if (*bytes_read == -1)
	{
		free (line->chars);
		line->chars = NULL;
		return (-1);
	}
	return (0);
}

/* ----------------------------- FUNC 5 ------------------------------------- */
void	line_write(t_line *line, t_buffer *buffer)
{
	while (buffer->read_head <= buffer->write_head)
	{
		if (buffer->chars[buffer->read_head] != '\n'
			&& buffer->chars[buffer->read_head] != '\0')
		{
			line_append_chars(line, buffer->chars[buffer->read_head]);
			buffer->read_head += 1;
		}
		else if (buffer->chars[buffer->read_head] == '\n')
		{
			line_append_chars(line, buffer->chars[buffer->read_head]);
			buffer->read_head += 1;
			line_append_chars(line, 0);
			line->filled -= 1;
			break ;
		}
		else if (buffer->chars[buffer->read_head] == '\0')
		{
			line_append_chars(line, '\0');
			line->filled -= 1;
			break ;
		}
		else
			break ;
	}
}
