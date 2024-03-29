/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ericshints.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/20 10:19:32 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* -------------------------- DEFINES --------------------------------------- */
# define FALSE 0
# define TRUE 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

typedef struct s_buffer
{
	char		chars[BUFFER_SIZE + 1];
	int			write_head;
	int			read_head;
	int			newly_created;
	ssize_t		bytes_read;
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
void	line_create(t_line *line, int *error_flag);
void	line_destroy(t_line *line);
int		buffer_has_data(t_buffer *buffer, int *error_flag);
char	buffer_next_char(t_buffer *buffer, int fd, int	*error_flag);
void	line_append_char(t_line *line, char c, int *error_flag);
void	ft_bzero(void *s, size_t n);

#endif
