/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:49:00 by alanghan          #+#    #+#             */
/*   Updated: 2021/08/24 10:09:30 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*cp;

	i = 0;
	cp = (char *)s;
	while (cp[i] != '\0')
	{
		if (cp[i] == (char)c)
			return (&cp[i]);
		i++;
	}
	if (cp[i] == (char)c)
		return (&cp[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*js;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	js = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!js)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		js[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		js[i] = s2[j];
		i++;
		j++;
	}
	js[i] = '\0';
	return (js);
}
