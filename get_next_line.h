/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/28 11:36:47 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>	// for definition of 'NULL' & 'size_t'---------------------------
# include <stdlib.h>	// for malloc & free ----------------------------------------
# include <unistd.h>	// for read -------------------------------------------------

/* -------------------------- DEFINES --------------------------------------- */
typedef struct s_string
{
	char	*chars;
	int		allocated;
	int		filled;
}					t_string;

/* -------------------------- PROTOTYPES ------------------------------------ */
char	*get_next_line(int fd);
void	string_create(t_string *string);
void	string_correct_chars(t_string *string, char *buf, int *i);
void	string_append_chars(t_string *string, char c);
char	*string_as_c_string(t_string *string, char **line);
void	string_destroy(t_string *string);

#endif
