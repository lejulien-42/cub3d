/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:19:04 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/12 21:46:03 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
	return (dest);
}
