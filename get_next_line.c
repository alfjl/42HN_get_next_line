/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/20 10:38:09 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
** 1.) change the BUFFER_SIZE malloced for line in .c and _utils.c. e.g. fixed value like 64, or BETTER: 1,5 of the last time!
** 2.) last check if return NULL or line.chars: if check == TRUE, just use function to write NULL in line.chars, and only have 1 return value, not two!
*/
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
	error_flag = FALSE;
	buffer_create(&buffer);
	line_create(&line, &error_flag);
	while (buffer_has_data(&buffer, &error_flag))
	{
		c = buffer_next_char(&buffer, fd, &error_flag);
		line_append_char(&line, c, &error_flag);
		if (c == '\n')
			break ;
	}
	if (error_flag == TRUE || (buffer.bytes_read == 0 && line.filled == 1))
		line_destroy(&line); // ------- 2. FIXED ---------
	return (line.chars);
}

/* ----------------------------- FUNC 2 ------------------------------------- */
void	buffer_create(t_buffer *buffer)
{
	if (!buffer->chars[0])
	{
		ft_bzero(buffer->chars, BUFFER_SIZE + 1);
		buffer->write_head = BUFFER_SIZE;
		buffer->read_head = 0;
		buffer->newly_created = TRUE;
		buffer->bytes_read = 1;
	}
}

/* ----------------------------- FUNC 3 ------------------------------------- */
void	line_create(t_line *line, int *error_flag)
{
	line->chars = (char *)malloc(sizeof(char) * 64); // ------- 1. SEMI FIXED ---------
	if (line->chars == NULL)
		*error_flag = TRUE;
	else
	{
		ft_bzero(line->chars, 64); // ------- 1. SEMI FIXED ---------
		line->allocated = 63; // ------- 1. SEMI FIXED ---------
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
