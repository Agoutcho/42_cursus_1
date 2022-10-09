/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:59:15 by atchougo          #+#    #+#             */
/*   Updated: 2022/06/25 16:27:53 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*saver[OPEN_MAX];
	int			reader;
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	reader = 1;
	while (reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if ((reader == -1) || (reader == 0 && saver[fd] == NULL))
			return (NULL);
		buffer[reader] = '\0';
		ft_switch(&saver[fd], buffer);
		if (ft_strchr(saver[fd], '\n'))
			return (ft_dispatch(&saver[fd]));
	}
	if (saver[fd] && !saver[fd][0])
		tmp = NULL;
	else
		tmp = ft_strdup(saver[fd]);
	free(saver[fd]);
	saver[fd] = NULL;
	return (tmp);
}
