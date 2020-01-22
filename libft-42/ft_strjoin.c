/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:03:35 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/08 06:20:53 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		allocplace;
	char	*writeptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	allocplace = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(s3 = malloc(allocplace * sizeof(char))))
		return (0);
	writeptr = s3;
	while (*s1 != '\0')
	{
		*writeptr++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*writeptr++ = *s2++;
	}
	*writeptr++ = '\0';
	return (s3);
}
