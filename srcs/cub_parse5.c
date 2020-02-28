/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 21:04:59 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/28 21:41:26 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void
	ft_checkn(char *currentline, t_sort *sort)
{
	int i;

	i = 1;
	if (currentline[1] == 'O')
		currentline++;
	else
		ft_puterror("Error north texture\n");
	if (ft_whitespace(currentline[i]) != 1)
		ft_puterror("\e[33bonus Error\n");
	while (ft_whitespace(currentline[i]) == 1)
		i++;
	ft_getpath(currentline, sort, 0);
}

int
	strlennspace(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != ' ')
			i++;
		str++;
	}
	return (i);
}

t_mlx_data
	ft_set_mlx_datathree(void)
{
	t_mlx_data mlx_data;

	mlx_data.hasstamina = 1;
	mlx_data.biggest = 0;
	mlx_data.zbuffer = NULL;
	mlx_data.spriteorder = NULL;
	mlx_data.spritedistance = NULL;
	mlx_data.showbonus = 0;
	mlx_data.stamina = 100;
	return (mlx_data);
}

int
	ft_do_ninetext(t_mlx_data *data)
{
	int	color;

	color = data->s_lifeframe.data[((int)data->texposs_lifeframe &
		(data->s_lifeframe.height - 1)) * data->s_lifeframe.height +
		data->texxs_lifeframe];
	return (color);
}

int
	ft_do_ninetexttwo(t_mlx_data *data)
{
	int	color;

	color = data->s_wallfour.data[((int)data->texposs_wallfour &
		(data->s_wallfour.height - 1)) * data->s_wallfour.height +
		data->texxs_wallfour];
	return (color);
}
