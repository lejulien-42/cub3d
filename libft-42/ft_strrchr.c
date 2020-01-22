/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:44:42 by lejulien          #+#    #+#             */
/*   Updated: 2019/11/04 20:29:54 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		isbeforeend;
	int		isencounter;
	char	*tempptr;

	isbeforeend = 0;
	isencounter = 0;
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == c)
		{
			tempptr = (char *)s;
			isencounter = 1;
		}
		s++;
	}
	if (isencounter != 1)
		return (0);
	return (tempptr);
}
