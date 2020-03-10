/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 05:53:43 by lejulien          #+#    #+#             */
/*   Updated: 2020/03/10 04:40:43 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

char
	*ft_subspace(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc((strlennspace(str) + 1) * sizeof(char));
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

int
	ft_whitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v')
		return (1);
	return (0);
}

int
	closeit(void *param)
{
	(void)*param;
	exit(0);
	return (0);
}

t_pos
	ft_setpoint(int x, int y)
{
	t_pos point;

	point.x = x;
	point.y = y;
	return (point);
}

void
	ft_setplayer(double x, double y, t_mlx_data *data)
{
	data->posx = x;
	data->posy = y;
}
