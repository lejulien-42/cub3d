/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:15:04 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/12 21:46:37 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	char	*d;
	char	*s;
	size_t	n;
	size_t	lend;

	d = dst;
	s = (char *)src;
	n = dsize;
	while (n-- != 0 && *d != '\0')
		d++;
	lend = d - dst;
	n = dsize - lend;
	if (n == 0)
		return (lend + ft_strlen(src));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (lend + (s - src));
}
