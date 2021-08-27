/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/27 18:24:09 by alanghan         ###   ########.fr       */
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
		if (buf == NULL)
		{
			string_destroy(&string);
			return (NULL);
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
		printf("I'm here!!!!");
		string_correct_chars(&string, buf, &i);
		if (buf[i] == '\n')
		{
			string_append_chars(&string, '\n');
			i++;
			free(buf); // maybe not needed, if 'break' only breaks from 'if', not 'while'. Then another break point needed in 'while'!
			break;
		}
		if (buf != NULL)
			free(buf);
	}
	string_as_c_string(&string, &line);
	// ---------- End Pattern (free & return) --------
	string_destroy(&string);
	return (line);
}

/* ----------------------------- FUNC 2 ------------------------------------- */
void	string_create(t_string *string)
{
	string->chars = (char *)malloc(sizeof(char) * 1024);
	string->allocated = 1024;
	string->filled = 0;
}

/* ----------------------------- FUNC 3 ------------------------------------- */
void	string_correct_chars(t_string *string, char *buf, int *i)
{
	while (*i < BUFFER_SIZE)
	{
		if (buf[*i] != '\n' && buf[*i] != EOF)
			string_append_chars(string, buf[*i]);
	}
}

/* ----------------------------- FUNC 4 ------------------------------------- */
void	string_append_chars(t_string *string, char c)
{
	char	*temp;
	int		j;

	if (string->filled >= string->allocated)
	{
		temp = (char *)malloc(sizeof(char) * (string->filled + BUFFER_SIZE));
		if (temp == NULL)
		{
			string_destroy(string);
			//return (NULL);
		}
		else
		{
			j = 0;
			while (j < string->filled)
			{
				temp[j] = string->chars[j];
				j++;
			}
			//free(string->chars);
			string->chars = temp;
			string->allocated = string->filled + BUFFER_SIZE;
		}
	}
	string->filled++;
	string->chars[string->filled] = c;
}

/* ----------------------------- FUNC 5 ------------------------------------- */
char	*string_as_c_string(t_string *string, char **line)
{
	int		j;

	j = 0;
	while (j < string->filled)
	{
		*line[j] = string->chars[j];
		j++;
	}
	*line[j] = '\0';
	return (*line);
}

/* ----------------------------- FUNC 6 ------------------------------------- */
void	string_destroy(t_string *string)
{
	if (string->chars != NULL)
		free(string->chars);
	string->chars = NULL;
	string->allocated = 0;
	string->filled = 0;
}

// ############################ QUESTIONS ######################################
// 1.) How do error handling? e.g. miss malloc