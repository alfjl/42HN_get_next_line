/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/31 18:42:52 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	int				i;
	int				bytes_read;
	static t_buffer	buffer;
	t_line			line;

	// ---------- Guard Pattern ----------------------
	if (fd < 0)
		return (NULL);

	// ---------- Variable Initialization Pattern ----
	buffer_create(&buffer);
	line_create(&line);
	bytes_read = 0;

	// ---------- Main Body --------------------------
	while (bytes_read >= 0)
	{
		buffer_write(&buffer, &bytes_read, fd);
		line_write(&line, &buffer, &i);
	}
	buffer_destroy(&buffer);
	return (line.chars);
}
/* ----------------------------- FUNC 2 ------------------------------------- */
void	buffer_create(t_buffer *buffer)
{
	if (buffer == NULL)
	{
		// buffer->chars = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		// if (buffer->chars == NULL)
		// 	//return (NULL); // muss noch abgefangen werden!!!!!!
		buffer->write_head = BUFFER_SIZE;
		buffer->read_head = 0;
	}
}
/* ----------------------------- FUNC 3 ------------------------------------- */
void	line_create(t_line *line)
{
	line->chars = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (line->chars == NULL)
	{
		//buffer_destroy(&buffer); // muss noch implementiert werden!!!!!!
		//return (NULL); // muss noch abgefangen werden!!!!!!
	}
	line->allocated = BUFFER_SIZE;
	line->filled = 0;
}
/* ----------------------------- FUNC 4 ------------------------------------- */
void	buffer_destroy(t_buffer *buffer)
{
	// if (buffer->chars[0] != NULL)
	// 	free(buffer->chars);
	// buffer->chars = NULL;
	buffer->write_head = 0;
	buffer->read_head = 0;
}
/* ----------------------------- FUNC 5 ------------------------------------- */
void	buffer_write(t_buffer *buffer, int *bytes_read, int fd)
{
	if (buffer->read_head == buffer->write_head)
	{
		*bytes_read = read(fd, buffer->chars, BUFFER_SIZE);
	}
}
/* ----------------------------- FUNC 6 ------------------------------------- */
void	line_write(t_line *line, t_buffer *buffer, int *i)
{
	while (*i < BUFFER_SIZE)
	{
		if (buffer->chars[*i] != '\n' && buffer->chars[*i] != '\0')
		{
			//printf("STRING = %s, ALLOCATED = %i, FILLED = %i\n", string->chars, string->allocated, string->filled); // ######################## TPO #######################
			line_append_chars(line, buffer->chars[*i]);
			*i += 1;
		}
		else
			break;
	}
}
/* ----------------------------- FUNC 7 ------------------------------------- */
void	line_append_chars(t_line *line, char c)
{
	char	*temp;
	int		j;

	if (line->filled >= line->allocated)
	{
		temp = (char *)malloc(sizeof(char) * (line->filled + BUFFER_SIZE + 1));
		if (temp == NULL)
		{
			//return (NULL); // muss noch abgefangen werden!!!!!!
		}
		else
		{
			j = 0;
			while (j < line->filled)
			{
				temp[j] = line->chars[j];
				j++;
			}
			free(line->chars);
			line->chars = temp;
			line->allocated = line->filled + BUFFER_SIZE;
		}
	}
	line->chars[line->filled] = c;
	line->filled++;
}
/* ----------------------------- FUNC 8 ------------------------------------- */
/* ----------------------------- FUNC 9 ------------------------------------- */
/* ----------------------------- FUNC 10 ------------------------------------ */
