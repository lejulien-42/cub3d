/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:30:48 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/07 18:51:02 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int index;

	index = 0;
	while (s2[index] && s1[index] && index < (int)n)
	{
		if (s1[index] == s2[index])
		{
			index++;
		}
		else
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	}
	if (index == (int)n)
		return (0);
	if (s1[index] == '\0' || s2[index] == '\0')
	{
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	}
	return (0);
}
