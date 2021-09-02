/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/02 11:38:39 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* -------------------------- DEFINES --------------------------------------- */
# define __NEWLINE__ -2 // needed??? not found in code!
# define __OFF__ 0
# define __ON__ 1

typedef struct s_buffer
{
	char	chars[BUFFER_SIZE + 1];
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
void	buffer_create(t_buffer *buffer, int *newly_created);
int		line_create(t_line *line);
void	buffer_destroy(t_buffer *buffer);
void	buffer_write(t_buffer *buffer, int *bytes_read, int fd, int *newly_created);
void	line_write(t_line *line, t_buffer *buffer);
void	line_append_chars(t_line *line, char c);
void	ft_bzero(void *s, size_t n);

#endif
