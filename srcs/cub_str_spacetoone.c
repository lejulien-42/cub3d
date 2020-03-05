/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_str_spacetoone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 03:48:48 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/05 06:01:46 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

char
	*ft_str_spacetoone(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	while (i < ft_strlen(str))
	{
		if (str[i] == ' ')
			res[i] = '1';
		else
			res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
