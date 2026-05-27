/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumei <mumei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:17:17 by myazawa           #+#    #+#             */
/*   Updated: 2026/05/27 18:45:10 by mumei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_str(char *buf, int byts)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (byts == 0)
		return (NULL);
	while (i < byts && buf[i] && buf[i] != '\n')
		i++;
	if (i < byts)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (buf[j] && j < i)
	{
		str[j] = buf[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
