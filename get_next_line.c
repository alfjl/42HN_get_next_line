/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/02 16:47:55 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	int				newly_created;
	int				bytes_read;
	static t_buffer	buffer;
	t_line			line;

	// ---------- Guard Pattern ----------------------
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// ---------- Variable Initialization Pattern ----
	bytes_read = 1;
	newly_created = __OFF__;
	buffer_create(&buffer, &newly_created);
	if (line_create(&line) == 0)
		return (NULL);
	// ---------- Main Body --------------------------
	while (bytes_read >= 0)
	{
		if (buffer_write(&buffer, &bytes_read, fd, &newly_created) == -1)
		{
			free (line.chars);
			return (NULL);
		}
		line_write(&line, &buffer);
		if (line.chars[line.filled - 1] == '\n')
			break;
		if (bytes_read ==0  && buffer.chars[buffer.read_head] == '\0') // if I put an "if" here, theres one KO switched to OK, but 2 OKs switched to KOs.
			break;
	}
	if (ft_strlen(line.chars) == 0)
	{
		free(line.chars);
		return (NULL);
	}
	return (line.chars);
}
/* ----------------------------- FUNC 2 ------------------------------------- */
void	buffer_create(t_buffer *buffer, int *newly_created)
{
	// if (buffer->chars == NULL)
	if (!buffer->chars[0]) // change to correct test! Don't use "!".
	{
		ft_bzero(buffer->chars, BUFFER_SIZE);
		buffer->write_head = BUFFER_SIZE;
		buffer->read_head = 0;
		*newly_created = __ON__;
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
int	buffer_write(t_buffer *buffer, int *bytes_read, int fd, int *newly_created)
{
	if (*newly_created == __ON__ ||
		buffer->read_head >= buffer->write_head)
	{
		*bytes_read = read(fd, buffer->chars, BUFFER_SIZE);
		buffer->read_head = 0;
		buffer->write_head = *bytes_read;
		buffer->chars[*bytes_read] = '\0';
	}
	if (*bytes_read == -1)
		return (-1);
	return (0);
}
/* ----------------------------- FUNC 5 ------------------------------------- */
void	line_write(t_line *line, t_buffer *buffer)
{
	while (buffer->read_head < buffer->write_head)
	{
		if (buffer->chars[buffer->read_head] != '\n' && buffer->chars[buffer->read_head] != '\0')
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
			break;
		}
		else if (buffer->chars[buffer->read_head] == '\0')
		{
			line_append_chars(line, '\0');
			line->filled -= 1;
			break;
		}
		else
			break;
	}
}
/* ----------------------------- FUNC 6 ------------------------------------- */
void	line_append_chars(t_line *line, char c)
{
	char	*temp;
	int		j;

	if (line->filled >= line->allocated)
	{
		temp = (char *)malloc(sizeof(char) * (line->filled + BUFFER_SIZE + 1));
		if (temp == NULL)
		{ // noch loeschen
			//return (NULL); // muss noch abgefangen werden!!!!!!
		}  // noch loeschen
		else
		{
			j = 0;
			while (j < line->filled)
			{
				temp[j] = line->chars[j];
				j++;
			}
			free(line->chars);
			line->chars = NULL;
			line->chars = temp;
			line->allocated = line->filled + BUFFER_SIZE;
		}
	}
	line->chars[line->filled] = c;
	line->filled++;
}
/* ----------------------------- FUNC 7 ------------------------------------- */
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
/* ----------------------------- FUNC 8 ------------------------------------- */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
/* ----------------------------- FUNC 9 ------------------------------------- */

/* ----------------------------- FUNC 10 ------------------------------------ */
