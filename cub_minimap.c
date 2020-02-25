/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:44:18 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 05:22:11 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void
	ft_putsquare_minimap(int i, int j, t_mlx_data *mlxdata, int rgb)
{
	mlxdata->square = ft_set_square(mlxdata->resph, mlxdata->resph,
		10 + j * mlxdata->resph, 10 + i * mlxdata->resph);
	ft_mlx_drawfilled_square(&mlxdata->square, rgb, mlxdata);
}

static int
	ft_checkoab(char c)
{
	if (c == '0' || c == 'A' || c == 'B')
		return (1);
	return (0);
}

void
	ft_mlx_show_minimap(t_mlx_data *mlxdata, t_sort *sort)
{
	int	i;
	int	j;

	i = 0;
	mlxdata->resph = sort->resh * 0.20 / sort->mapheight;
	while (ft_strlen(mlxdata->map[i]))
	{
		j = 0;
		while (mlxdata->map[i][j])
		{
			if (mlxdata->map[i][j] == '1')
				ft_putsquare_minimap(i, j, mlxdata, rgb_int(0, 204, 153));
			else if (mlxdata->map[i][j] == '2')
				ft_putsquare_minimap(i, j, mlxdata, rgb_int(0, 200, 0));
			else if (mlxdata->map[i][j] == '3')
				ft_putsquare_minimap(i, j, mlxdata, rgb_int(0, 0, 200));
			else if (ft_checkoab(mlxdata->map[i][j]))
				ft_putsquare_minimap(i, j, mlxdata, rgb_int(255, 255, 255));
			else
				ft_putsquare_minimap(i, j, mlxdata, rgb_int(255, 0, 0));
			j++;
		}
		i++;
	}
	ft_showposes(mlxdata);
}
