/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:07:07 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/12 21:45:29 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	unsigned char *ptr;
	unsigned char *ptr2;

	ptr = (unsigned char *)d;
	ptr2 = (unsigned char *)s;
	while (n-- > 0)
	{
		*ptr = *ptr2;
		if (*ptr2 == (unsigned char)c)
		{
			ptr++;
			return (ptr);
		}
		ptr++;
		ptr2++;
	}
	return (0);
}
