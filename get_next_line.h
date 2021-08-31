/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_TEST.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/31 18:28:34 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* -------------------------- DEFINES --------------------------------------- */
# define __NEWLINE__ -2

typedef struct s_buffer
{
	char	chars[BUFFER_SIZE];
	int		write_head;
	int		read_head;
}					t_buffer;

typedef struct s_line
{
	char	*chars;
	int		allocated;
	int		filled;
}					t_line;

/* -------------------------- PROTOTYPES ------------------------------------ */
char	*get_next_line(int fd);
void	buffer_create(t_buffer *buffer);
void	line_create(t_line *line);
void	buffer_destroy(t_buffer *buffer);
void	buffer_write(t_buffer *buffer, int *bytes_read, int fd);
void	line_write(t_line *line, t_buffer *buffer, int *i);
void	line_append_chars(t_line *line, char c);

#endif
