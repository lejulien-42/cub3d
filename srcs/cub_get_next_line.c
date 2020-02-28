/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 01:57:21 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 21:55:52 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft-42/libft.h"
#include "./get_next_line.h"
#include <stdlib.h>

int		ft_hasnl(char *str)
{
	int		i;

	i = 0;
	if (!str || str[i] == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_read(int fd, char **buffer)
{
	int		len;
	char	*whatiread;
	char	*tmp;

	len = BUFFER_SIZE;
	if (!(whatiread = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (NULL);
	while (ft_hasnl(*buffer) == -1 && len == BUFFER_SIZE)
	{
		len = read(fd, whatiread, BUFFER_SIZE);
		whatiread[len] = 0;
		if (!(tmp = ft_strjoingnl(*buffer, whatiread)))
			return (NULL);
		if (*buffer != 0)
			free(*buffer);
		if (!(*buffer = ft_strdup(tmp)))
			return (NULL);
		free(tmp);
	}
	free(whatiread);
	return (*buffer);
}

t_char	*ft_cut(char *buffer)
{
	t_char	*cut;
	int		nlpos;

	if (!(cut = malloc(sizeof(t_char))))
		return (NULL);
	nlpos = ft_hasnl(buffer);
	buffer[nlpos] = '\0';
	if (!(cut->toline = ft_strdup(buffer)))
		return (NULL);
	if (!(cut->tobuff = ft_strdup(&buffer[nlpos + 1])))
		return (NULL);
	free(buffer);
	return (cut);
}

int		get_next_line(int fd, char **line)
{
	static char	*buffer = NULL;
	t_char		*res;

	if (line)
		*line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1
			|| !(buffer = ft_read(fd, &buffer)) || !line)
		return (-1);
	if (ft_hasnl(buffer) == -1)
	{
		*line = buffer;
		buffer = NULL;
		return (0);
	}
	if (!(res = ft_cut(buffer)))
		return (-1);
	*line = res->toline;
	buffer = res->tobuff;
	free(res);
	return (1);
}
