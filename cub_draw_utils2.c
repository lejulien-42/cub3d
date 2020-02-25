/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 15:35:23 by lejulien          #+#    #+#             */
/*   Updated: 2020/02/25 07:15:40 by lejulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "./libft-42/libft.h"

void
	ft_mlx_drawfilled_square(t_square *square, int color, t_mlx_data *datamlx)
{
	int	i;

	i = 0;
	while (i < square->w)
	{
		ft_mlx_vertline(datamlx, color, &square->pos, square->h);
		square->pos.x++;
		i++;
	}
}
