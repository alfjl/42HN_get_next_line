/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/23 10:06:29 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	static char	*stat_buffer = NULL;	// static variable to buffer the whole output for later display (initialize with NULL/0/'0'?)
	char		*buf;					// string variable to buffer output of one while loop, and later append to static_buffer
	int			read_bytes;				// variable to safe the number of bytes read from read()

	// ---------- Guard Pattern ----------------------
	if (fd < 0)	// this handles the return of '-1' from open() in main(), if file couldn't be read!
		return (NULL);

	// ---------- Variable Initialization Pattern ----
	read_bytes = 0;
	buf = (char *)malloc(((BUFFER_SIZE + 1) * sizeof(char)));

	// ---------- Main Body --------------------------
	while ((read_bytes = read(fd, buf, BUFFER_SIZE)) > 0)	// if read() does not return 0 for EOF, or -1 for error
		{
			
		}

	//read(fd, buf, BUFFER_SIZE)


	// ---------- End Pattern (free & return) --------

	return (stat_buffer);
}
