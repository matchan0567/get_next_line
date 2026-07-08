/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myazawa <myazawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:28:50 by mumei             #+#    #+#             */
/*   Updated: 2026/07/08 20:36:27 by myazawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*trim_save_str(char **save, char **tmp)
{
	char	*str;

	str = ft_substr(*tmp, 0, ft_strlen(*tmp) - ft_strlen(ft_strchr(*tmp, '\n'))
			+ 1);
	*save = ft_substr(*tmp, ft_strlen(*tmp) - ft_strlen(ft_strchr(*tmp, '\n'))
			+ 1, ft_strlen(ft_strchr(*tmp, '\n')) - 1);
	free(*tmp);
	if (*save && **save == '\0')
	{
		free(*save);
		*save = NULL;
	}
	return (str);
}

static char	*negbyts_free(char **buf, char **str, char **tmp)
{
	if (buf && *buf)
		free(*buf);
	if (str && *str)
		free(*str);
	if (tmp && *tmp)
		free(*tmp);
	return (NULL);
}

static char	*bts_value(char **str, char **save, int byts)
{
	if (byts == 0)
	{
		if (*str && **str == '\0')
		{
			free(*str);
			return (NULL);
		}
		return (*str);
	}
	return (trim_save_str(save, str));
}

static char	*buf_to_str(char **tmp, char **save, int fd)
{
	char	*buf;
	char	*str;
	int		byts;

	str = NULL;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	byts = read(fd, buf, BUFFER_SIZE);
	if (byts < 0)
		return (negbyts_free(&buf, &str, tmp));
	buf[byts] = '\0';
	str = ft_strjoin_free(*tmp, buf);
	*tmp = NULL;
	while (byts > 0 && ft_strchr(str, '\n') == NULL)
	{
		byts = read(fd, buf, BUFFER_SIZE);
		if (byts < 0)
			return (negbyts_free(&buf, &str, tmp));
		buf[byts] = '\0';
		str = ft_strjoin_free(str, buf);
	}
	free(buf);
	return (bts_value(&str, save, byts));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save)
	{
		tmp = ft_strdup(save);
		free(save);
		if (ft_strchr(tmp, '\n') != NULL)
			return (trim_save_str(&save, &tmp));
		else
			save = NULL;
	}
	else
		tmp = NULL;
	return (buf_to_str(&tmp, &save, fd));
}
