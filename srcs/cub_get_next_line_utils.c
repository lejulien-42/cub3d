/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_next_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 00:35:11 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 21:56:03 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft-42/libft.h"

char	*ft_strjoingnl(char const *s1, char const *s2)
{
	char	*s3;
	int		allocplace;
	char	*writeptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	allocplace = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(s3 = malloc(allocplace * sizeof(char))))
		return (0);
	writeptr = s3;
	while (*s1 != '\0')
		*writeptr++ = *s1++;
	while (*s2 != '\0')
		*writeptr++ = *s2++;
	*writeptr++ = '\0';
	return (s3);
}
