/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/27 16:40:51 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>	// for definition of 'NULL' & 'size_t'---------------------------
# include <stdlib.h>	// for malloc & free ----------------------------------------
# include <unistd.h>	// for read -------------------------------------------------

/* -------------------------- DEFINES --------------------------------------- */
// # define __FAIL__ -1
// # define __SUCCESS__ 1 // do I need that, or not? (ret value of ft_join_read)--------

typedef struct s_string
{
	char			*chars;
	unsigned int	allocated;
	unsigned int	filled;
}					t_string;

/* -------------------------- PROTOTYPES ------------------------------------ */
char	*get_next_line(int fd);



#endif
