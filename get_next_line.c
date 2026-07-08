/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumei <mumei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:28:50 by mumei             #+#    #+#             */
/*   Updated: 2026/07/08 18:16:32 by mumei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*trim_save_str(char **save, char **tmp)
{
	char	*str;

	str = ft_substr_free(*tmp, 0, ft_strlen(*tmp) - ft_strlen(ft_strchr(tmp,
					'\n')) + 1);
	*save = ft_substr_free(*tmp, ft_strlen(ft_strchr(*tmp, '\n')),
			ft_strlen(ft_strchr(*tmp, '\n')) - 1);
	return (str);
}

static char	*buf_to_str(char **tmp, char **save, int fd)
{
	char	*buf;
	char	*str;
	int		byts;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	byts = read(fd, buf, BUFFER_SIZE);
	if (byts < 0)
		return (negbyts_free(&buf, &str));
	buf[byts] = '\0';
	str = ft_strjoin_free(tmp, buf);
	while (byts > 0 && ft_strchr(str, '\n') == NULL)
	{
		byts = read(fd, buf, BUFFER_SIZE);
		if (byts < 0)
			return (negbyts_free(&buf, &str));
		buf[byts] = '\0';
		str = ft_strjoin_free(str, buf);
	}
	free(buf);
	if (byts == 0)
		return (str);
	return (trim_save_str(&save, &str));
}

static char	*negbyts_free(char **buf, char **str)
{
	free(*buf);
	free(*str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*tmp;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save)
	{
		tmp = ft_strdup(save);
		free(save);
		if (ft_strchr(save, '\n') != NULL)
			return (trim_save_str(&save, &tmp));
		else
			save = NULL;
	}
	else
		tmp = NULL;
	return (buf_to_str(&tmp, &save, fd));
}
