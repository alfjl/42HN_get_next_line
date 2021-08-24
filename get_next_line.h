/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/24 10:11:25 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>	// for definition of 'NULL' & 'size_t'---------------------------

/* -------------------------- DEFINES --------------------------------------- */
# define __FAIL__ -1
# define __SUCCESS__ 1 // do I need that, or not? (ret value of ft_join_read)--------

/* -------------------------- PROTOTYPES ------------------------------------ */
char	*get_next_line(int fd);
int		ft_join_read(char **static_buf, char **buf);

#endif
