/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_ericshints.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbrTRUEn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:49:00 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/09 16:52:32 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
int	buffer_has_data(t_buffer *buffer, int *error_flag)
{
	if (buffer->bytes_read <= 0 || *error_flag == TRUE)
		return (0);
	return (1);
}

/* ----------------------------- FUNC 2 ------------------------------------- */
char	buffer_next_char(t_buffer *buffer, int fd, int	*error_flag)
{
	char	c;

	c = '\0';
	if (buffer->newly_created == TRUE
		|| buffer->read_head >= buffer->write_head)
	{
		buffer->bytes_read = read(fd, buffer->chars, BUFFER_SIZE);
		if (buffer->bytes_read == -1)
			*error_flag = TRUE;
		else
		{
			buffer->read_head = 0;
			buffer->write_head = buffer->bytes_read;
			buffer->chars[buffer->bytes_read] = '\0';
			buffer->newly_created = FALSE;
		}
	}
	c = buffer->chars[buffer->read_head];
	buffer->read_head += 1;
	return (c);
}

/* ----------------------------- FUNC 3 ------------------------------------- */
void	line_append_char(t_line *line, char c, int *error_flag)
{
	char	*temp;
	int		j;

	if (line->filled >= line->allocated)
	{
		temp = (char *)malloc(sizeof(char) * (line->filled + 64)); // ------- 1. SEMI FIXED ---------
		if (temp == NULL)
			*error_flag = TRUE;
		else
		{
			ft_bzero(temp, line->filled + 64); // ------- 1. SEMI FIXED ---------
			j = 0;
			while (j < line->filled)
			{
				temp[j] = line->chars[j];
				j++;
			}
			free(line->chars);
			line->chars = NULL;
			line->chars = temp;
			line->allocated = line->filled + 63; // ------- 1. SEMI FIXED ---------
		}
	}
	if (*error_flag == FALSE)
		line->chars[line->filled++] = c;
}

/* ----------------------------- FUNC 4 ------------------------------------- */
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
