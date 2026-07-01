/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myazawa <myazawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:23:26 by myazawa           #+#    #+#             */
/*   Updated: 2026/07/01 16:08:50 by myazawa          ###   ########.fr       */
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

	if (save)
	{
		if (ft_strchr(save, '\n') != NULL)
		{
			tmp = ft_strdup(save);
			free(save);
			str = ft_substr(tmp, 0, ft_strlen(ft_strchr(tmp, '\n')) + 1);
			save = ft_substr(tmp, ft_strlen(ft_strchr(tmp, '\n')) + 1,
					ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n')) - 1);
			free(tmp);
			return (str);
		}
		else
		{
			tmp = ft_strdup(save);
			free(save);
		}
	}
}
