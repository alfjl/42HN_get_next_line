/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/24 10:05:39 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	static char	*static_buf = NULL;	// static variable to buffer the whole output for later display (initialize with NULL/0/'0'?)
	char		*buf;					// string variable to buffer output of one while loop, and later append to static_buffer
	int			read_bytes;				// variable to safe the number of bytes read from read()

	// ---------- Guard Pattern ----------------------
	if (fd < 0) // this handles the return of '-1' from open() in main(), if file couldn't be read!
		return (NULL);

	// ---------- Variable Initialization Pattern ----
	read_bytes = 0;

	// ---------- Main Body --------------------------
	// while ((read_bytes = read(fd, buf, BUFFER_SIZE)) > 0)	// if read() does not return 0 for EOF, or -1 for error  --> NORMINETTE ERROR: Assignment in controle structure
	while (read_bytes >= 0) // if read() does not return -1 for error (if return 0 for EOF, we still have to process the last read bytes)
		{
			// malloc size for first buffer (but if no '\n' in BUFFER-SIZE, we keep on reading, so we need new malloced buff more often!)
			buf = (char *)malloc(((BUFFER_SIZE + 1) * sizeof(char)));
			if (buf == NULL)
				return (NULL);
			// read chars BUFFER_SIZE into read_bytes
			read_bytes = read(fd, buf, BUFFER_SIZE);
			if (read_bytes < 0)
			{
				free(buf);
				return (NULL);
			}
			ft_join_read(&static_buf, &buf);
			// if theres already a '\n', cut static_buf down and return (see below). QUESTION: What to do with read_bytes? Do we need that for next round to step in correctly?
			if (ft_strchr(buf, '\n') != NULL)
				ft_cut_line(&static_buf, &buf, &read_bytes); // do I need to include 'read_bytes' here, to shorten to correct length, for later run?   |   to make code shorter, use 'return (ft_cut_line(...))'. But first try to only use one return value at end of function!
			// if there's EOF (read_bytes == 0)
			else if (read_bytes == 0)
				ft_cut_last_line(&static_buf, &buf);
		}
	// ---------- End Pattern (free & return) --------
	// free something!
	return (&static_buf);
}

int	ft_join_read(char **static_buf, char **buf)	// ############## too long ###############
{
	// variables for: 1. joined string, 2. index overall, 3. index per string
	char	*temp;
	size_t	i;
	size_t	j;

	// PROTECT
	if (static_buf == NULL || buf == NULL)	// this will lead to problems, with first round, since static_buf is initialized with 'NULL'
		return (__FAIL__);
	// allocate enough memory for both strings, PROTECT and join strings into temp!
	temp = ft_strjoin(*static_buf, *buf);
	// free buf
	free(buf);
	// free static_buf
	free(static_buf);
	// point static_buf to temp
	static_buf = temp;
	// free temp
	free(temp);
	return (__SUCCESS__); // or better return value, like length of new 'static_buf'?
}
