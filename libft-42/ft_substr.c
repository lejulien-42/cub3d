/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 00:29:53 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/12 23:32:10 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static void	*ft_memcpys(void *restrict dest, const void *restrict src, size_t n)
{
	unsigned char *ptr;
	unsigned char *ptr2;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (dest == src)
		return (dest);
	if (!src)
		return (0);
	while (n-- > 0)
	{
		*ptr = *ptr2;
		ptr++;
		ptr2++;
	}
	*ptr = '\0';
	return (dest);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *res;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!(res = malloc((len + 1) * sizeof(char))))
		return (0);
	res = ft_memcpys(res, s + start, len);
	return (res);
}
