/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 06:23:30 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/08 19:27:45 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static void	*ft_memcpys(void *restrict dest, const void *restrict src, size_t n)
{
	unsigned char *ptr;
	unsigned char *ptr2;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (n-- > 0)
	{
		*ptr = *ptr2;
		ptr++;
		ptr2++;
	}
	*ptr = '\0';
	return (dest);
}

static int	ft_strtlen(char *start, char *end)
{
	int		cnt;

	cnt = 0;
	while (start != end)
	{
		cnt++;
		start++;
	}
	return (cnt);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*s3;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	while (*s1 != '\0' && ft_isinset(*s1, set))
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	start = (char *)s1;
	while (*s1 != '\0')
		s1++;
	s1--;
	while (ft_isinset(*s1, set))
		s1--;
	end = (char *)s1;
	if (start == end)
		return (ft_strdup(""));
	if (!(s3 = malloc((ft_strtlen(start, end) + 2) * sizeof(char))))
		return (0);
	s3 = ft_memcpys(s3, start, ft_strtlen(start, end) + 1);
	return (s3);
}
