/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumei <mumei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:23:26 by myazawa           #+#    #+#             */
/*   Updated: 2026/07/01 18:25:57 by mumei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*str;
	char		*tmp;
	int			byts;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save)
	{
		if (ft_strchr(save, '\n') != NULL)
		{
			tmp = ft_strdup(save);
			free(save);
			str = ft_substr_free(tmp, 0, ft_strlen(ft_strchr(tmp, '\n')) + 1);
			save = ft_substr_free(tmp, ft_strlen(ft_strchr(tmp, '\n')) + 1,
					ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n')) - 1);
			return (str);
		}
		else
		{
			tmp = ft_strdup(save);
			free(save);
		}
	}
	else
		tmp = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!buf)
		return (NULL);
	byts = read(fd, buf, BUFFER_SIZE);
	if (byts < 0)
	{
		free(buf);
		return (NULL);
	}
	buf[byts] = '\0';
	str = ft_strjoin(tmp, buf);
	free(tmp);
	while (byts > 0 && ft_strchr(str, '\n') == NULL)
	{
		byts = read(fd, buf, BUFFER_SIZE);
		if (byts < 0)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[byts] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	if (byts == 0)
		return (str);
	tmp = str;
	str = ft_substr_free(tmp, 0, ft_strlen(ft_strchr(tmp, '\n')) + 1);
	save = ft_substr_free(tmp, ft_strlen(ft_strchr(tmp, '\n')) + 1,
			ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n')) - 1);
	return (str);
}
