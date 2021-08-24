/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:33:56 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/24 17:14:38 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
char	*get_next_line(int fd)
{
	// ---------- Variable Declaration Pattern -------
	static char	*static_buf = "";	// static variable to buffer the whole output for later display (initialize with NULL/0/'0'?)
	char		*buf;					// string variable to buffer output of one while loop, and later append to static_buffer
	int			bytes_read;				// variable to safe the number of bytes read from read()

	// ---------- Guard Pattern ----------------------
	if (fd < 0) // this handles the return of '-1' from open() in main(), if file couldn't be read!
		return (NULL);

	// ---------- Variable Initialization Pattern ----
	bytes_read = 0;

	// ---------- Main Body --------------------------
	// while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)	// if read() does not return 0 for EOF, or -1 for error  --> NORMINETTE ERROR: Assignment in controle structure
	while (bytes_read >= 0) // if read() does not return -1 for error (if return 0 for EOF, we still have to process the last read bytes)
		{
			// malloc size for first buffer (but if no '\n' in BUFFER-SIZE, we keep on reading, so we need new malloced buf more often!)
			buf = (char *)malloc(((BUFFER_SIZE + 1) * sizeof(char)));
			if (buf == NULL)
				return (NULL);
			// read chars BUFFER_SIZE into bytes_read
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				free(buf);
				free(static_buf); // is this needed? is static_buf malloced somewhere?
				return (NULL);
			}
			// append buf to static_buf
			ft_join_read(&static_buf, &buf, bytes_read);
			//printf("\nstatic_buf is: %s\n", static_buf); // ---------------------------- TPO ----------------------------------
			//printf("\nbytes_read are: %i\n", bytes_read); // ---------------------------- TPO ----------------------------------
			//printf("\nstatic_buf is: %s\n", static_buf); // ---------------------------- TPO ----------------------------------
			// if theres already a '\n', cut static_buf down and return (see below).
			if (ft_strchr(static_buf, '\n') != NULL)
			{ // ---------------------------- TPO ----------------------------------
				// printf("\nIN '\\n'\n");	// ---------------------------- TPO ----------------------------------
				ft_cut_line(&static_buf, &bytes_read); // to make code shorter, use 'return (ft_cut_line(...))'. But first, try to only use one return value at end of function!
			} // ---------------------------- TPO ----------------------------------
			// if there's EOF (bytes_read == 0)
			else if (bytes_read == 0)
				ft_cut_last_line(&static_buf); // to make code shorter, use 'return (ft_cut_last_line(...))'. But first, try to only use one return value at end of function!
			printf("\nEND OF WHILE\n"); // ---------------------------- TPO ----------------------------------
		}
	// ---------- End Pattern (free & return) --------
	// free everything needed! // (not static_buf, since this is needed in overarching function (e.g. main()))
	return (static_buf);
}
/* ----------------------------- FUNC 2 ------------------------------------- */
int	ft_join_read(char **static_buf, char **buf, int bytes_read)	// ############## too long ###############
{
	// variables for: 1. joined string
	char	*temp;

	// PROTECT
	if (static_buf == NULL || buf == NULL)	// this will lead to problems, with first round, since static_buf is initialized with 'NULL'
		return (__FAIL__);
	//printf("\nbuf is: %s\n", *buf); // ---------------------------- TPO ----------------------------------
	*(buf)[bytes_read] = '\0';
	// allocate enough memory for both strings, PROTECT and join strings into temp!
	//printf("\nstatic_buf is: %s\n", *static_buf); // ---------------------------- TPO ----------------------------------
	temp = ft_strjoin(*static_buf, *buf);
	//printf("\nstatic_buf is: %s\n", *static_buf); // ---------------------------- TPO ----------------------------------
	// free buf
	free(*buf);
	// free static_buf
	//free(*static_buf);
	// point static_buf to temp
	*static_buf = temp;
	// free temp
	free(temp);
	return (__SUCCESS__); // or better return value, like length of new 'static_buf'?
}
/* ----------------------------- FUNC 3 ------------------------------------- */
int	ft_cut_line(char **static_buf, int	*bytes_read)
{
	// variables: 1. temporary storage cut down string
	char	*temp;

	printf("IN FT_CUT_LINE"); // ---------------------------- TPO ----------------------------------
	// copy static_buf until '\n' into temp
	temp = ft_substr(*static_buf, 0, ft_strchr(*static_buf, '\n') - *static_buf + 1); // is '*static_buf' here correct, or is it just dereferencing the string?
	if (temp == NULL)
	{
		free(temp);
		//free (static_buf); // needed here? or handled in function above?
		return (__FAIL__); // or return NULL?
	}
	//free the static_buf // do I need that here? Is the static_buf even allocated?
	//free(static_buf);
	/* ------------- second step: using a function to copy value into static_buf, which already mallocs ( = fewer lines) ------ */
	// allocate memory for static_buf
	static_buf = (char **)malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (static_buf == NULL)
	{
		free(temp);
		//free (static_buf); // needed here? or handled in function above?
		return (__FAIL__); // or return NULL?
	}
	*static_buf = temp;
	/* ------------------------------------------------------------------------------------------------------------------------ */
	free(temp);
	*bytes_read = -1; // do I need that here, to later jump out of loop?
	return (__SUCCESS__);
}
/* ----------------------------- FUNC 4 ------------------------------------- */
int	ft_cut_last_line(char **static_buf)
{
	// variables: 1. temporary storage cut down string
	char	*temp;

	// copy static_buf until '\n' into temp
	temp = ft_substr(*static_buf, 0, ft_strchr(*static_buf, EOF) - *static_buf); // is '*static_buf' here correct, or is it just dereferencing the string?
	if (temp == NULL)
	{
		free(temp);
		free (static_buf); // needed here? or handled in function above?
		return (__FAIL__); // or return NULL?
	}
	//free static_buf
	free(static_buf);
	/* ------------- second step: using a function to copy value into static_buf, which already mallocs ( = fewer lines) ------ */
	// allocate memory for static_buf
	static_buf = (char **)malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (static_buf == NULL)
	{
		free(temp);
		free (static_buf); // needed here? or handled in function above?
		return (__FAIL__); // or return NULL?
	}
	*static_buf = temp;
	/* ------------------------------------------------------------------------------------------------------------------------ */
	free(temp);
	return (__SUCCESS__);
}
