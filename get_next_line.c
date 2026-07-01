/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myazawa <myazawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 22:33:36 by myazawa           #+#    #+#             */
/*   Updated: 2026/06/24 18:27:13 by myazawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define FLAG_DUP 1
#define FLAG_JOIN -1

char	*get_next_line(int fd)
{
	static char	*save;
	char		*str;
	int			len;
	char		*tmp;

	str = NULL;
	if (save && ft_strchr(save, '\n') != NULL)
	{
		tmp = free_strjoin_dup(save, NULL, FLAG_DUP);
		len = ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n')) + 1;
		save = ft_strdup(ft_strchr(tmp, '\n') + 1);
		str = free_strjoin_dup(tmp, NULL, FLAG_DUP);
		return (sft_substr(str, 0, len));
	}
	else if (save)
		tmp = free_strjoin_dup(save, NULL, FLAG_DUP);
	str = save_str(tmp, fd);
	if (ft_strchr(str, '\n') == NULL)
		return (str);
	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '\n')) + 1;
	save = free_strjoin_dup(str, NULL, FLAG_DUP);
	return (ft_substr(str, 0, len));
}

static char	*save_str(char *str, int fd)
{
	char	*buf;
	char	*tmp;
	int		byts;

	byts = 1;
	buf = readbuf(fd);
	if (!buf)
		return (NULL);
	if (!str)
		str = free_strjoin_dup(buf, NULL, FLAG_DUP);
	else
	{
		tmp = str;
		str = free_strjoin_dup(tmp, buf, FLAG_JOIN);
	}
	while (byts > 0 && ft_strchr(buf, '\n') == NULL)
	{
		byts = read(fd, buf, BUFFER_SIZE);
		buf[byts] = '\0';
		tmp = str;
		str = free_strjoin_dup(tmp, buf, FLAG_JOIN);
	}
	free(buf);
	return (str);
}

char	*readbuf(int fd)
{
	int		byts;
	char	*buf;

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
	return (buf);
}

static char	*free_strjoin_dup(char *s1, char *s2, int frag)
{
	char	*str;

	if (!s1)
		return (NULL);
	if (frag == FLAG_DUP || !s2)
	{
		str = ft_strdup(s1);
		free(s1);
	}
	if (frag == FLAG_JOIN)
	{
		str = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (str);
}

static char	*free_substr(char *s, unsigned int start, size_t len)
{
	char	str;

	str = ft_substr(s, start, len);
	free(s);
	return (str);
}
