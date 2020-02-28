/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 00:35:55 by lejulien          #+#    #+#             */
/*   Updated: 2020/01/03 02:43:03 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_char
{
	char *tobuff;
	char *toline;
}				t_char;

int				get_next_line(int fd, char **line);
t_char			*ft_cut(char *buffer);
int				ft_hasnl(char *str);
char			*ft_strjoingnl(char const *s1, char const *s2);
#endif
