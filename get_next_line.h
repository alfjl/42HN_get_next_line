/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 10:23:01 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/24 15:20:20 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* -------------------------- INCLUDES -------------------------------------- */
# include <stdio.h>	// for definition of 'NULL' & 'size_t'---------------------------
# include <stdlib.h>	// for malloc & free ----------------------------------------
# include <unistd.h>	// for read -------------------------------------------------

/* -------------------------- DEFINES --------------------------------------- */
# define __FAIL__ -1
# define __SUCCESS__ 1 // do I need that, or not? (ret value of ft_join_read)--------

/* -------------------------- PROTOTYPES ------------------------------------ */
char	*get_next_line(int fd);
int		ft_join_read(char **static_buf, char **buf, int bytes_read);
int		ft_cut_line(char **static_buf, int	*read_bytes);
int		ft_cut_last_line(char **static_buf);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif
