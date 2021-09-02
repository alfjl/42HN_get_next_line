/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:49:00 by alanghan          #+#    #+#             */
/*   Updated: 2021/09/02 17:19:59 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ----------------------------- FUNC 1 ------------------------------------- */
void	line_append_chars(t_line *line, char c)
{
	char	*temp;
	int		j;

	if (line->filled >= line->allocated)
	{
		temp = (char *)malloc(sizeof(char) * (line->filled + BUFFER_SIZE + 1));
		if (temp == NULL)
		{// noch loeschen
			//return (NULL); // muss noch abgefangen werden!!!!!!
		}// noch loeschen
		else
		{
			j = 0;
			while (j < line->filled)
			{
				temp[j] = line->chars[j];
				j++;
			}
			free(line->chars);
			line->chars = NULL;
			line->chars = temp;
			line->allocated = line->filled + BUFFER_SIZE;
		}
	}
	line->chars[line->filled] = c;
	line->filled++;
}

/* ----------------------------- FUNC 2 ------------------------------------- */
int	line_determine_null(t_line *line)
{
	if (ft_strlen(line->chars) == 0)
	{
		free(line->chars);
		return (0);
	}
	return (1);
}

/* ----------------------------- FUNC 3 ------------------------------------- */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	cs = s;
	i = 0;
	while (i < n)
	{
		cs[i] = '\0';
		i++;
	}
}

/* ----------------------------- FUNC 4 ------------------------------------- */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/* ----------------------------- FUNC 5 ------------------------------------- */
