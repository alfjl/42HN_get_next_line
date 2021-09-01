/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/01 11:41:58 by alanghan         ###   ########.fr       */
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
	printf("READ_HEAD BEGINNING = %d\n", buffer.read_head); // ######################## TPO #######################

	// ---------- Variable Initialization Pattern ----
	buffer_create(&buffer);
	line_create(&line);
	// ---------- Main Body --------------------------
	while (bytes_read >= 0)
	{
		i = 0;
		buffer_write(&buffer, &bytes_read, fd);
		line_write(&line, &buffer, &i);
		if (line.chars[line.filled - 1] == '\n')
			break;
		else if (bytes_read == 0 && buffer.chars[i] == '\0')
			break;
	}
	//buffer_destroy(&buffer);
	return (line.chars);
}
/* ----------------------------- FUNC 2 ------------------------------------- */
void	buffer_create(t_buffer *buffer)
{
	// if (buffer->chars == NULL)
	if (!buffer->chars[0]) // change to correct test! Don't use "!".
	{
		ft_bzero(buffer->chars, BUFFER_SIZE);
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
		//buffer_destroy(&buffer); // muss noch implementiert werden!!!!!! Eigentlich nicht, da BUFFER nicht gemalloced!!!
		//return (NULL); // muss noch abgefangen werden!!!!!!
	}
	ft_bzero(line->chars, BUFFER_SIZE + 1);
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
	if ((buffer->read_head == 0 && buffer->write_head > 0) ||
		buffer->read_head == buffer->write_head)
	{
		*bytes_read = read(fd, buffer->chars, BUFFER_SIZE);
		buffer->read_head = 0;
	}
}
/* ----------------------------- FUNC 6 ------------------------------------- */
void	line_write(t_line *line, t_buffer *buffer, int *i)
{
	while (*i < BUFFER_SIZE)
	{
		if (buffer->chars[*i] != '\n' && buffer->chars[*i] != '\0')
		{
			//printf("LINE = %s, ALLOCATED = %i, FILLED = %i\n", line->chars, line->allocated, line->filled); // ######################## TPO #######################
			line_append_chars(line, buffer->chars[*i]);
			*i += 1;
			buffer->read_head += 1;
		}
		else if (buffer->chars[*i] == '\n')
		{
			line_append_chars(line, buffer->chars[*i]);
			*i += 1;
			buffer->read_head += 1;
			line_append_chars(line, '\0');
			line->filled -= 1;
			break;
		}
		else
			break;
	}
	printf("BUFFER = %s\n", buffer->chars); // ######################## TPO #######################
	printf("LINE = %s\n", line->chars); // ######################## TPO #######################
	printf("READ_HEAD = %d\n", buffer->read_head); // ######################## TPO #######################
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
		{ // delete later
			//return (NULL); // muss noch abgefangen werden!!!!!!
		} // delete later
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
	//write(1, &line->chars[line->filled - 1], 33); // ########## TPO #############
}
/* ----------------------------- FUNC 8 ------------------------------------- */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	cs = s;
	i = 0;
	while (i < n)
	{
		cs[i] = '\0';
		i++;
	}
}
/* ----------------------------- FUNC 9 ------------------------------------- */
/* ----------------------------- FUNC 10 ------------------------------------ */
