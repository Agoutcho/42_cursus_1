/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:42:38 by atchougo          #+#    #+#             */
/*   Updated: 2022/06/25 16:27:32 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_switch(char **s, char *buffer)
{
	char	*tmp;

	if (*s)
	{
		tmp = *s;
		*s = ft_strjoin(tmp, buffer);
		free(tmp);
		return ;
	}
	*s = ft_strdup(buffer);
}

static char	*ft_dispatch(char **s)
{
	char	*tmp;
	char	*displayed_line;

	tmp = *s;
	*s = ft_strdup(ft_strchr(tmp, '\n') + 1);
	displayed_line = ft_strndup(tmp, ft_strlen(tmp) - ft_strlen(*s));
	free(tmp);
	return (displayed_line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*saver = NULL;
	int			reader;
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	reader = 1;
	while (reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if ((reader == -1) || (reader == 0 && saver == NULL))
			return (NULL);
		buffer[reader] = '\0';
		ft_switch(&saver, buffer);
		if (ft_strchr(saver, '\n'))
			return (ft_dispatch(&saver));
	}
	if (saver && !saver[0])
		tmp = NULL;
	else
		tmp = ft_strdup(saver);
	free(saver);
	saver = NULL;
	return (tmp);
}
