/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/27 13:38:50 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	static int	i = 0;
	int			bytes_read;
	char		*buf;
	char		*line;
	t_string	string;

	// ---------- Guard Pattern ----------------------
	if (fd < 0)
		return (NULL);

	// ---------- Variable Initialization Pattern ----
	string_create(&string);
	bytes_read = 0;

	// ---------- Main Body --------------------------
	while (bytes_read >= 0)
	{
		i = 0;
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		bytes_read = read(fd, buf, BUFFER_SIZE);
		string_correct_chars(&string, buf, &i);
		if (buf[i] == '\n')
		{
			string_append_chars('\n');
			i++;
			free(buf); // maybe not needed, if 'break' only breaks from 'if', not 'while'. Then another break point needed in 'while'!
			break;
		}
		free(buf);
	}
	line = string_as_c_string(&string);
	// ---------- End Pattern (free & return) --------
	string_destroy(&string);
	return (line);
}
/* ----------------------------- FUNC 2 ------------------------------------- */
	string_create(&string);
/* ----------------------------- FUNC 3 ------------------------------------- */
string_correct_chars(&string, buf, &i)
/* ----------------------------- FUNC 4 ------------------------------------- */
string_append_chars('\n')
/* ----------------------------- FUNC 5 ------------------------------------- */
string_as_c_string(&string)
/* ----------------------------- FUNC 6 ------------------------------------- */
string_destroy(&string)
/* ----------------------------- FUNC 6 ------------------------------------- */
string_append_chars()